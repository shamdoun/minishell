/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 22:13:42 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/09 22:15:07 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern volatile sig_atomic_t	g_stop_signal;

void	handle_signal(int sig)
{
	static int	nl;

	if (g_stop_signal == 1 || g_stop_signal == 2 || g_stop_signal == -1)
		nl = 0;
	else if (g_stop_signal == 3)
		nl = 1;
	if (sig == 2)
	{
		if (!nl)
			write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
