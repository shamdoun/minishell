/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:19:20 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/15 10:35:04 by shamdoun         ###   ########.fr       */
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

static void	pipe_child_runs_binary(char *cmd_path,
		char **args_list, t_shell *shell)
{
	int	rv;

	signal(SIGQUIT, &handle_quit_signal);
	rv = execve(cmd_path, args_list, shell->env);
	if (rv < 0)
		printf("error after execve of %d: \n", errno);
}

static void	run_child(char *cmd_path, char **args_list, t_shell *shell)
{
	int	rv;

	if (ft_is_executable(cmd_path))
		handle_all_signals(1);
	else
		signal(SIGINT, &handle_ctrl_c_for_child);
	rv = execve(cmd_path, args_list, shell->env);
	if (rv)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(shell->all_input->command_name, 2);
		perror(" ");
		if (errno == ENOENT)
		{
			ft_malloc(0, -4);
			exit (127);
		}
		if (errno == ENOEXEC || errno == EACCES)
		{
			ft_malloc(0, -4);
			exit (126);
		}
		exit(1);
	}
}

void	run_binary(char *cmd_path, int mode, char **args_list, t_shell *shell)
{
	pid_t	child;
	int		status;

	if (mode)
	{
		if (!ft_is_executable(cmd_path))
			handle_all_signals(3);
		else
			(signal(SIGINT, SIG_IGN), signal(SIGQUIT, SIG_IGN));
		child = fork();
		if (child < 0)
			fork_error();
		if (child == 0)
			run_child(cmd_path, args_list, shell);
		waitpid(child, &status, 0);
		if (WIFEXITED(status))
			add_new_status(shell, WEXITSTATUS(status));
		else
			add_new_status(shell, 128 + WTERMSIG(status));
		handle_all_signals(0);
	}
	else
		pipe_child_runs_binary(cmd_path, args_list, shell);
}

int empty_string(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	execute_other_commands(t_shell *shell, int mode)
{
	char	**args_list;
	char	*cmd_path;
	int		c;
	char	*cmd_name;

	cmd_name = shell->all_input->command_name;
	if (empty_string(cmd_name))
	{
		error_arg_status_update(NO_COMMAND, cmd_name, shell, 127);
		return ;
	}
	set_args_list(shell, &args_list);
	cmd_path = find_command_path(cmd_name, shell);
	c = execution_case(cmd_path, shell);
	if (c == 1 && ft_strncmp(cmd_name, "./minishell", 11))
		make_file_executable(&args_list, cmd_name, &cmd_path);
	if (c == 2 || (c == 3
			&& !ft_strncmp(cmd_name, "./minishell", 11)))
		cmd_path = ft_strdup(cmd_name);
	if (c == 3 && ft_strncmp(cmd_name, "./minishell", 11))
		make_file_executable(&args_list, cmd_name, &cmd_path);
	if (c == 4 || c == 5 || (!c && !cmd_path && !ft_strncmp(cmd_name, "./", 2)))
		cmd_path = ft_strdup(cmd_name);
	if (c == 6)
		cmd_path = NULL;
	if (c == 7)
		return ;
	if (cmd_path)
		run_binary(cmd_path, mode, args_list, shell);
	else
		error_arg_status_update(NO_COMMAND, cmd_name, shell, 127);
}
