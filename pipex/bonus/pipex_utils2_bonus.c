/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:52:39 by shamdoun          #+#    #+#             */
/*   Updated: 2024/04/24 13:36:36 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "../../libft/libft.h"

void	create_pipes(t_pipe *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		if (pipe(pipex->ends + 2 * i) < 0)
			error_exit("failed to create pipes!", 1);
		i++;
	}
}

void	close_all_fd(t_pipe pipex)
{
	int	i;	

	i = 0;
	close(pipex.infile);
	close(pipex.outfile);
	while (i < (pipex.cmd_count - 1) * 2)
	{
		close(pipex.ends[i]);
		i++;
	}
}

void	here_doc(t_pipe *pipex, char *limiter)
{
	int		fd;
	char	*line;
	int		w_r;

	fd = open(".new_input", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (!fd)
		error_exit("failed to create here_open file", 1);
	// unlink(".new_input");
	while (1)
	{
		write(1, "pipe heredoc> ", 15);
		line = get_next_line(0);
		if (!line)
			error_exit("failed to retrieve user input!", 1);
		if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
			break ;
		w_r = write(fd, line, ft_strlen(line));
		free(line);
		if (!w_r)
			error_exit("failed to write to here_open file!", 1);
	}
	free(line);
	pipex->infile = fd;
}

void	open_files(t_pipe *pipex, char **argv, int argc)
{
	if (!pipex->here_open)
		pipex->infile = open(argv[1], O_RDONLY);
	else
		here_doc(pipex, argv[2]);
	if (pipex->infile < 0)
		error_exit("open sysc has failed!", 1);
	if (pipex->here_open)
		pipex->outfile = open(argv[argc - 1],
				O_CREAT | O_RDWR | O_APPEND, 0777);
	else
		pipex->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (pipex->outfile < 0)
		error_exit("open sys has failed!", 1);
}
