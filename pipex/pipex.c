/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:12:07 by shamdoun          #+#    #+#             */
/*   Updated: 2024/04/13 15:37:12 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../libft/libft.h"

void	close_fd(t_pipe pipex)
{
	close(pipex.ends[0]);
	close(pipex.ends[1]);
	close(pipex.outfile);
	close(pipex.infile);
}

void	init(t_pipe *pipex, char **argv, int argc, char **envp)
{
	char	*path;

	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
		error_exit("open sysc for input has failed!", 1);
	pipex->outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (pipex->outfile < 0)
		error_exit("open sys for output has failed!", 1);
	if (pipe(pipex->ends) < 0)
		error_exit("pipe init has failed!", 1);
	path = getpath(envp);
	pipex->cmd_paths = ft_split(path, ':');
	if (!pipex->cmd_paths)
	{
		close_fd(*pipex);
		error_exit("failed to allocate space on the heap!", 1);
	}
}

void	first_child(t_pipe pipex, char **argv, char **envp)
{
	if (dup2(pipex.ends[1], STDOUT_FILENO) < 0)
	{
		close_fd(pipex);
		free_array(pipex.cmd_paths);
	}
	if (dup2(pipex.infile, STDIN_FILENO) < 0)
	{
		close_fd(pipex);
		free_array(pipex.cmd_paths);
	}
	close_fd(pipex);
	execute_cmd(pipex, argv, envp, 2);
}

void	second_child(t_pipe pipex, char **argv, char **envp)
{
	if (dup2(pipex.outfile, STDOUT_FILENO) < 0)
	{
		close_fd(pipex);
		free_array(pipex.cmd_paths);
		exit(EXIT_FAILURE);
	}
	if (dup2(pipex.ends[0], STDIN_FILENO) < 0)
	{
		close_fd(pipex);
		free_array(pipex.cmd_paths);
		exit(EXIT_FAILURE);
	}
	close_fd(pipex);
	execute_cmd(pipex, argv, envp, 3);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	pipex;
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
		error_exit("incorrect number of arguments", 0);
	init(&pipex, argv, argc, envp);
	pid1 = fork();
	if (pid1 < 0)
	{
		close_fd(pipex);
		free_array(pipex.cmd_paths);
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
		first_child(pipex, argv, envp);
	pid2 = fork();
	if (pid2 < 0)
	{
		close_fd(pipex);
		free_array(pipex.cmd_paths);
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0)
		second_child(pipex, argv, envp);
	close_fd(pipex);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	free_array(pipex.cmd_paths);
	exit(EXIT_SUCCESS);
}
