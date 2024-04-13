/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:40:42 by shamdoun          #+#    #+#             */
/*   Updated: 2024/04/13 15:38:33 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "../../libft/libft.h"

void	execute_cmd(t_pipe pipex, char **argv, char **envp, int i)
{
	pipex.cmd_args = ft_split(argv[2 + pipex.here_open + i], ' ');
	if (!pipex.cmd_args)
	{
		free(pipex.ends);
		free_array(pipex.cmd_paths);
		error_exit("failed to allocate space with malloc!", 1);
	}
	pipex.cmd = get_cmd(pipex);
	if (!pipex.cmd)
	{
		free(pipex.ends);
		free_array(pipex.cmd_args);
		free_array(pipex.cmd_paths);
		error_exit("could not retrieve the command", 1);
	}
	if (execve(pipex.cmd, pipex.cmd_args, envp) == -1)
	{
		free(pipex.ends);
		free_array(pipex.cmd_args);
		free_array(pipex.cmd_paths);
		error_exit("failed to execute command!", 1);
	}
}

void	child(t_pipe pipex, char **argv, char **envp, int i)
{
	if (!i)
	{
		if (dup2(pipex.infile, STDIN_FILENO) == -1)
		{
			close_all_fd(pipex);
			free_allocated_space(pipex);
			exit(EXIT_FAILURE);
		}
		if (dup2(pipex.ends[1], STDOUT_FILENO) == -1)
		{
			close_all_fd(pipex);
			free_allocated_space(pipex);
			exit(EXIT_FAILURE);
		}
	}
	else if (i > 0 && i != pipex.cmd_count - 1)
	{
		if (dup2(pipex.ends[2 * i - 2], STDIN_FILENO) == -1)
		{
			close_all_fd(pipex);
			free_allocated_space(pipex);
			exit(EXIT_FAILURE);
		}
		if (dup2(pipex.ends[2 * i + 1], STDOUT_FILENO) == -1)
		{
			close_all_fd(pipex);
			free_allocated_space(pipex);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (dup2(pipex.ends[2 * i - 2], STDIN_FILENO) == -1)
		{
			close_all_fd(pipex);
			free_allocated_space(pipex);
			exit(EXIT_FAILURE);
		}
		if (dup2(pipex.outfile, STDOUT_FILENO) == -1)
		{
			close_all_fd(pipex);
			free_allocated_space(pipex);
			exit(EXIT_FAILURE);
		}
	}
	close_all_fd(pipex);
	execute_cmd(pipex, argv, envp, i);
}

void	init(t_pipe *pipex, char **argv, int argc, char **envp)
{
	char	*path;

	open_files(pipex, argv, argc);
	if (pipex->here_open)
		pipex->cmd_count = argc - 4;
	else
		pipex->cmd_count = argc - 3;
	pipex->ends = (int *)malloc(sizeof(int) * 2 * (pipex->cmd_count - 1));
	if (!pipex->ends)
		error_exit("failed to make the pipes!", 1);
	create_pipes(pipex);
	path = getpath(envp);
	pipex->cmd_paths = ft_split(path, ':');
	if (!pipex->cmd_paths)
	{
		close_all_fd(*pipex);
		free(pipex->ends);
		error_exit("failed to allocate space on the heap!", 1);
	}
}

int	check_args(t_pipe *pipex, char **argv)
{
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		pipex->here_open = 1;
		return (6);
	}
	pipex->here_open = 0;
	return (5);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	pipex;
	pid_t	pid;
	int		i;

	if (argc < check_args(&pipex, argv))
		error_exit("insufficient number of arguments", 0);
	init(&pipex, argv, argc, envp);
	i = 0;
	while (i < pipex.cmd_count)
	{
		pid = fork();
		if (pid < 0)
		{
			close_all_fd(pipex);
			free_allocated_space(pipex);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
			child(pipex, argv, envp, i);
		i++;
	}
	close_all_fd(pipex);
	waitpid(-1, NULL, 0);
	free_allocated_space(pipex);
	exit(EXIT_SUCCESS);
}
