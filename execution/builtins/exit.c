/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 22:04:07 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/09 22:04:59 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_last_status(t_status *list)
{
	t_status	*head;

	head = list;
	if (!head)
		return (0);
	while (head->next)
		head = head->next;
	return (head->status);
}

void	exit_shell(t_shell *shell, t_arg *status)
{
	int	value;

	while (shell->all_allocated_data)
	{
		free(shell->all_allocated_data->address);
		free(shell->all_allocated_data);
		shell->all_allocated_data = shell->all_allocated_data->next;
	}
	if (status)
	{
		value = ft_atoi(status->arg);
		exit(value);
	}
	else
		exit(ft_last_status(shell->all_status));
}
