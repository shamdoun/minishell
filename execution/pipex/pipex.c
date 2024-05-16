/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:12:16 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/16 15:53:30 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	create_pipes(int **ends, int count)
{
	int	i;

	*ends = malloc(sizeof(int) * 2 * count);
	if (!(*ends))
		return (1);
	i = 0;
	while (i < count)
	{
		if (pipe((*ends) + 2 * i))
			return (1);
		i++;
	}
	return (0);
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

int	init_pipex(t_pipex **pipex, t_shell *shell)
{
	*pipex = malloc(sizeof(t_pipex));
	if (!(*pipex))
		return (1);
	(*pipex)->pipe_count = count_nbr_of_pipes(shell->all_input);
	if (create_pipes(&(*pipex)->ends, (*pipex)->pipe_count))
		return (1);
	(*pipex)->processes = malloc(sizeof(int) * ((*pipex)->pipe_count + 1));
	if (!(*pipex)->processes)
		return (1);
	return (0);
}

void	pipex(t_shell *shell, int mode)
{
	t_pipex	*pipex;
	pid_t	child;
	int		i;

	if (init_pipex(&pipex, shell))
	{
		add_new_status(shell, 1);
		return ;
	}
	i = 0;
	signal(SIGINT, &handle_signal_for_bin), signal(SIGQUIT,&handle_quit_signal);
	while (i < pipex->pipe_count + 1)
	{
		child = fork();
		if (child < 0)
		{
			add_new_status(shell, 1);
			return ;
		}
		if (!child)
		{
			if (duplicate_ends(shell, pipex->ends, pipex->pipe_count, i))
				exit (1);
			(run_built_ins(shell, mode), exit(ft_last_status(shell->all_status)));
		}
		pipex->processes[i] = child;
		close(shell->all_input->in_file);
		if (shell->all_input->here_doc)
			close(shell->all_input->here_doc);
		shell->all_input = shell->all_input->next;
		i++;
	}
	close_ends_and_wait(pipex->pipe_count, pipex->ends, pipex->processes, shell);
	(signal(SIGINT, &handle_signal),signal(SIGQUIT, SIG_IGN));
}
