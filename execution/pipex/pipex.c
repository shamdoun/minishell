/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:12:16 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/13 21:28:09 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	create_pipes(int **ends, int count)
{
	int	i;

	*ends = malloc(sizeof(int) * 2 * count);
	if (!(*ends))
		exit(1);
	i = 0;
	while (i < count)
	{
		pipe((*ends) + 2 * i);
		i++;
	}
}

int	count_nbr_of_pipes(t_input *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i - 1);
}

void	init_pipex(t_pipex **pipex, t_shell *shell)
{
	*pipex = malloc(sizeof(t_pipex));
	if (!(*pipex))
		exit(1);
	(*pipex)->pipe_count = count_nbr_of_pipes(shell->all_input);
	create_pipes(&(*pipex)->ends, (*pipex)->pipe_count);
	(*pipex)->processes = malloc(sizeof(int) * ((*pipex)->pipe_count + 1));
	if (!(*pipex)->processes)
		exit(1);
}

void	pipex(t_shell *shell, int mode)
{
	t_pipex	*pipex;
	pid_t	child1;
	int		i;

	init_pipex(&pipex, shell);
	i = 0;
	while (i < pipex->pipe_count + 1)
	{
		signal(SIGINT, &handle_signal_for_bin);
		child1 = fork();
		if (!child1)
		{
			duplicate_ends(shell, pipex->ends, pipex->pipe_count, i);
			(run_built_ins(shell, mode), exit(1));
		}
		pipex->processes[i] = child1;
		close(shell->all_input->in_file);
		if (shell->all_input->here_doc)
			close(shell->all_input->here_doc);
		shell->all_input = shell->all_input->next;
		i++;
	}
	close_ends_and_wait(pipex->pipe_count, pipex->ends, pipex->processes);
}
