/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:32:46 by shamdoun          #+#    #+#             */
/*   Updated: 2024/04/13 15:38:21 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "../../libft/libft.h"

char	*get_cmd(t_pipe pipex)
{
	char	*command;
	char	*tmp;

	if (access(pipex.cmd_args[0], F_OK | X_OK) == 0)
	{
		command = ft_strdup1(pipex.cmd_args[0]);
		return (command);
	}
	
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

void	free_allocated_space(t_pipe pipex)
{
	free(pipex.ends);
	free_array(pipex.cmd_paths);
}
