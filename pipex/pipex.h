/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:18:45 by shamdoun          #+#    #+#             */
/*   Updated: 2024/04/14 19:59:22 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>
# include <stdio.h>

typedef struct pipe
{
	int		infile;
	int		outfile;
	int		ends[2];
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
}	t_pipe;
char	*getpath(char **envp);
char	*get_cmd(t_pipe pipex);
void	free_array(char **a);
void	error_exit(char *error, int mode);
void	second_child(t_pipe pipex, char **argv, char **envp);
void	first_child(t_pipe pipex, char **argv, char **envp);
void	execute_cmd(t_pipe pipex, char **argv, char **envp, int i);
void	close_fd(t_pipe pipex);
void	init(t_pipe *t_pipe, char **argv, int argc, char **envp);
int		pipex(int argc, char **argv, char **envp);

#endif