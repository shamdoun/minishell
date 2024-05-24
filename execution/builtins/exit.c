/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 22:04:07 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/24 17:10:36 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
extern volatile sig_atomic_t	g_signal;

int	ft_last_status(t_status *list)
{
	t_status	*head;
	
	if (g_signal == 2)
	{
		g_signal = 0;
		return (1);
	}
	head = list;
	if (!head)
		return (0);
	while (head->next)
		head = head->next;
	return (head->status);
}

void	exit_shell(t_shell *shell, t_arg *status, int mode)
{
	int	value;

	//!TODO: free all allocated data!
	// while (shell->all_allocated_data)
	// {
	// 	free(shell->all_allocated_data->address);
	// 	free(shell->all_allocated_data);
	// 	shell->all_allocated_data = shell->all_allocated_data->next;
	// }
	if (mode)
		write(1, "exit\n", 5);
	if (status)
	{
		value = ft_atoi(status->arg);
		if (value == 255)
			exit(255);
		if (status->next)
		{
			perror("bash: exit: too many arguments");
			add_new_status(shell, 1);
		}
		else
			exit(value);
	}
	else
	{
		value = ft_last_status(shell->all_status);
		ft_malloc(0, 1);
		exit(value);
	}
}
