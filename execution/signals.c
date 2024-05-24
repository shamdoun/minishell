/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 22:13:42 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/24 20:27:31 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t	g_signal = 0;

void	handle_ctrl_c_for_parent(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_signal = 2;
}

void	handle_ctrl_c_for_child(int sig)
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

void	handle_quit_signal(int sig)
{
	(void)sig;
	write(2, "Quit: 3\n", 9);
}

void	handle_signal_heredoc(int sig)
{
	(void)sig;
	close(STDIN_FILENO);
	write(2, "\n", 1);
	g_signal = 1;
}

void	handle_all_signals(int mode)
{
	if (!mode)
	{
		(1) && (signal(SIGINT, &handle_ctrl_c_for_parent), signal(SIGQUIT, SIG_IGN));
	}
	else if (mode == 1)
		(1) && (signal(SIGINT, &handle_ctrl_c_for_child), signal(SIGQUIT, SIG_IGN));
	else if (mode == 2)
		signal(SIGINT, &handle_signal_heredoc);
	else if (mode == 3)
		(1) && (signal(SIGINT, &handle_signal_for_bin),signal(SIGQUIT, &handle_quit_signal));
}