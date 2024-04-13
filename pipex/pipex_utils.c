/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:25:07 by shamdoun          #+#    #+#             */
/*   Updated: 2024/04/13 15:37:10 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../libft/libft.h"

char	*get_cmd(t_pipe pipex)
{
	char	*command;
	char	*tmp;

	while (*pipex.cmd_paths)
	{
		tmp = ft_strjoin(*pipex.cmd_paths, "/");
		if (!tmp)
			return (NULL);
		command = ft_strjoin(tmp, pipex.cmd_args[0]);
		free(tmp);
		if (!command)
			return (NULL);
		if (access(command, F_OK | X_OK) == 0)
			return (command);
		free(command);
		pipex.cmd_paths++;
	}
	return (NULL);
}

char	*getpath(char **envp)
{
	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH", 4))
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

void	execute_cmd(t_pipe pipex, char **argv, char **envp, int i)
{
	pipex.cmd_args = ft_split(argv[i], ' ');
	if (!pipex.cmd_args)
	{
		free_array(pipex.cmd_paths);
		error_exit("failed to allocate space with malloc!", 1);
	}
	pipex.cmd = get_cmd(pipex);
	if (!pipex.cmd)
	{
		free_array(pipex.cmd_args);
		free_array(pipex.cmd_paths);
		error_exit("could not retrieve the command", 1);
	}
	if (execve(pipex.cmd, pipex.cmd_args, envp) == -1)
	{
		free_array(pipex.cmd_args);
		free_array(pipex.cmd_paths);
		error_exit("failed to execute the command!", 1);
	}
}

void	error_exit(char *error, int mode)
{
	if (mode)
		perror(error);
	else
		ft_putstr_fd(error, 1);
	exit(1);
}

void	free_array(char **a)
{
	int	i;

	i = 0;
	while (a[i])
	{
		free(a[i]);
		i++;
	}
	free(a);
}
