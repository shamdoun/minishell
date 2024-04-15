/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:29:45 by shamdoun          #+#    #+#             */
/*   Updated: 2024/04/14 20:08:43 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <fcntl.h>
# include <stdio.h>
# include "../gnl/get_next_line.h"

typedef struct pipe
{
	int		infile;
	int		outfile;
	int		*ends;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
	int		cmd_count;
	int		here_open;
}	t_pipe;

char	*getpath(char **envp);
char	*get_cmd(t_pipe pipex);
void	error_exit(char *error, int mode);
void	free_array(char **a);
void	free_allocated_space(t_pipe pipex);
void	create_pipes(t_pipe *pipex);
int		check_args(t_pipe *pipex, char **argv);
void	here_doc(t_pipe *pipex, char *limiter);
void	close_all_fd(t_pipe pipex);
void	execute_cmd(t_pipe pipex, char **argv, char **envp, int i);
void	child(t_pipe pipex, char **argv, char **envp, int i);
void	init(t_pipe *pipex, char **argv, int argc, char **envp);
void	open_files(t_pipe *pipex, char **argv, int argc);
int		pipex_bonus(int argc, char **argv, char **envp);
#endif