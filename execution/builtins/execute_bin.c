/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:19:20 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/26 16:20:59 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_split_list(char ***args_list, char *data)
{
	char	**new_list;

	new_list = ft_malloc(sizeof(char *) * (list_len(*args_list) + 2), 0);
	if (!new_list)
		return ;
	new_list[0] = ft_strdup(data);
	if (!new_list)
		return ;
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
		if (!ft_is_executable(cmd_path))
			handle_all_signals(3);
		else
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
		}
		child = fork();
		if (child == 0)
		{
			if (ft_is_executable(cmd_path))
				handle_all_signals(1);
			else
				signal(SIGINT, &handle_ctrl_c_for_child);
			rv = execve(cmd_path, args_list, shell->env);
			if (rv)
			{
				fprintf(stderr, "bash: %s: is a directory\n", args_list[0]);
				exit(126);
			}
		}
		waitpid(child, &status, 0);
		if (WIFEXITED(status))
			add_new_status(shell, WEXITSTATUS(status));
		else
			add_new_status(shell, 128 + WTERMSIG(status));
		handle_all_signals(0);
	}
	else
		pipe_child_runs_binary(cmd_path, args_list, shell);
	// free(cmd_path);
}

void	set_args_list(t_shell *shell, char ***args_list)
{
	char	*joined_args;

	if (shell->all_input->args)
	{
		joined_args = ft_join_args(shell->all_input->args);
		if (!joined_args)
			return ;
		*args_list = ft_split_1(joined_args, ' ');
		if (!(*args_list))
			return ;
		update_split_list(args_list, shell->all_input->command_name);
	}
	else
	{
		*args_list = ft_split_1(shell->all_input->command_name, ' ');
		if (!(*args_list))
			return ;
		//printf("%s\n %s\n", shell->all_input->command_name, *(args_list)[0]);
	}
}

void	execute_other_commands(t_shell *shell, int mode)
{
	char	**args_list;
	char	*cmd_path;
	char	*path_env;
	
	set_args_list(shell, &args_list);
	cmd_path = find_command_path(shell->all_input->command_name, shell);
	path_env = ft_getenv("PATH", shell->env);
	if ((cmd_path && path_env) || (cmd_path && shell->r_path))
		run_binary(cmd_path, mode, args_list, shell);
	else
	{
		fprintf(stderr, "bash: %s: command not found\n", args_list[0]);
		add_new_status(shell, 127);
	}
}
