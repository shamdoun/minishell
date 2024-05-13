/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 22:13:42 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/13 21:41:53 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t	g_stop_signal = 0;

void	handle_signal(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_signal_for_bin(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	handle_child_signal(int sig)
{
	if (sig == 2)
		exit(130);
}

void	handle_quit_signal(int sig)
{
	(void)sig;
	write(2, "Quit: 3\n", 9);
}
