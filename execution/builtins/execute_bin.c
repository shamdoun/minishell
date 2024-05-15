/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:19:20 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/14 22:49:17 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	update_split_list(char ***args_list, char *data)
{
	char	**new_list;

	new_list = malloc(sizeof(char *) * (list_len(*args_list) + 2));
	if (!new_list)
		exit(1);
	new_list[0] = ft_strdup(data);
	if (!new_list)
		exit(1);
	ft_memcpy(&new_list[1], *args_list, list_len(*args_list) * sizeof(char *));
	new_list[list_len(*args_list) + 1] = NULL;
	*args_list = new_list;
}

void	pipe_child_runs_binary(char *cmd_path, char **args_list, t_shell *shell)
{
	int	rv;

	signal(SIGQUIT, &handle_quit_signal);
	rv = execve(cmd_path, args_list, shell->env);
	if (rv < 0)
		fprintf(stderr, "error of %d\n", errno);
}

void	run_binary(char *cmd_path, int mode, char **args_list, t_shell *shell)
{
	pid_t	child;
	int		rv;
	int		status;

	if (mode)
	{
		(signal(SIGINT, &handle_signal_for_bin),
			signal(SIGQUIT, &handle_quit_signal));
		child = fork();
		if (child == 0)
		{
			signal(SIGINT, &handle_child_signal);
			rv = execve(cmd_path, args_list, shell->env);
			if (rv)
				ft_lst_add_status_back(&shell->all_status,
					ft_lstnew_status(errno), shell);
		}
		waitpid(child, &status, 0);
		fprintf(stderr, "child status %d\n", WEXITSTATUS(status));
		add_new_status(shell, WEXITSTATUS(status));
		(signal(SIGINT, &handle_signal), signal(SIGQUIT, SIG_IGN));
	}
	else
		pipe_child_runs_binary(cmd_path, args_list, shell);
	free(cmd_path);
}

void	set_args_list(t_shell *shell, char ***args_list)
{
	char	*joined_args;

	if (shell->all_input->args)
	{
		joined_args = ft_join_args(shell->all_input->args);
		if (!joined_args)
			exit(1);
		*args_list = ft_split_1(joined_args, ' ');
		if (!(*args_list))
			exit(1);
		update_split_list(args_list, shell->all_input->command_name);
	}
	else
	{
		*args_list = ft_split_1(shell->all_input->command_name, ' ');
		if (!(*args_list))
			exit(1);
	}
}

void	execute_other_commands(t_shell *shell, int mode)
{
	char	**args_list;
	char	*cmd_path;

	set_args_list(shell, &args_list);
	cmd_path = find_command_path(args_list[0], shell);
	if (cmd_path)
		run_binary(cmd_path, mode, args_list, shell);
	else
	{
		fprintf(stderr, "bash: %s: command not found\n", args_list[0]);
		add_new_status(shell, 127);
	}
}
