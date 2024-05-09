/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:43:52 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/08 19:45:56 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_unused_here_docs(t_input *input)
{
	t_input	*head;

	head = input->next;
	while (head)
	{
		if (head->here_doc)
			close(head->here_doc);
		head = head->next;
	}
}

void	duplicate_ends(t_shell *shell, int *ends, int pipe_count, int i)
{
	int	j;

	if (i)
		dup2(ends[2 * i - 2], STDIN_FILENO);
	if (i != pipe_count)
		dup2(ends[2 * i + 1], STDOUT_FILENO);
	j = 0;
	while (j < pipe_count * 2)
	{
		close(ends[j]);
		j++;
	}
	close_unused_here_docs(shell->all_input);
}

void	close_ends_and_wait(int pipe_count, int *ends, int *processes)
{
	int	j;

	j = 0;
	while (j < pipe_count * 2)
	{
		close(ends[j]);
		j++;
	}
	j = 0;
	while (j < pipe_count + 1)
	{
		waitpid(processes[j], NULL, 0);
		j++;
	}
}
