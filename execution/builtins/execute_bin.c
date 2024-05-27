/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:19:20 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/27 19:29:31 by shamdoun         ###   ########.fr       */
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
				perror("minishell: ");
				if (errno == ENOENT)
					exit (127);
				if (errno == ENOEXEC || errno == EACCES)
					exit (126);
				exit(1);
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

int	correct_dir(char *cmd_path, char *cwd)
{
	char	**split1;
	char	**split2;
	split1 = ft_split_1(cmd_path, '/');
	if (!split1)
		return (0);
	split2 = ft_split_1(cwd, '/');
	if (!split2)
		return (0);
	if (!ft_strncmp(split1[list_len(split1) - 3], split2[list_len(split2) - 1], ft_strlen(split2[list_len(split2) - 1])))
		return (1);
	return (0);
}

void	make_file_executable(char ***args, char *file, char **cmd_path)
{
	*cmd_path = ft_strdup("/bin/bash");
	*args = ft_malloc(sizeof(char *) * 4, 1);
	if (!(*args))
		return ;
	(*args)[0] = *cmd_path;
	(*args)[1] = "-c";
	(*args)[2] = file;
	(*args)[3] = NULL;
}

void	execute_other_commands(t_shell *shell, int mode)
{
	char	**args_list;
	char	*cmd_path;
	
	set_args_list(shell, &args_list);
	cmd_path = find_command_path(shell->all_input->command_name, shell);
	if (cmd_path && (*shell->all_input->command_name == '.') && ((access(shell->all_input->command_name, F_OK | X_OK) == 0)) && !correct_dir(cmd_path, shell->cwd))
		make_file_executable(&args_list, shell->all_input->command_name, &cmd_path);
	if (cmd_path && (*shell->all_input->command_name == '.') && ((access(shell->all_input->command_name, F_OK | X_OK))) && !correct_dir(cmd_path, shell->cwd))
		cmd_path = ft_strdup1(shell->all_input->command_name);
	else if (!cmd_path && (access(shell->all_input->command_name, F_OK | X_OK) == 0) && (*shell->all_input->command_name == '.'))
		make_file_executable(&args_list, shell->all_input->command_name, &cmd_path);
	else if (!cmd_path && (access(shell->all_input->command_name, F_OK | X_OK)) && (*shell->all_input->command_name == '.'))
		cmd_path = ft_strdup1(shell->all_input->command_name);
	if (cmd_path)
	{
		run_binary(cmd_path, mode, args_list, shell);
		return ;
	}
	fprintf(stderr, "minishell: %s: command not found\n", args_list[0]);
	add_new_status(shell, 127);
}
