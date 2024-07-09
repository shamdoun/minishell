/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:42:28 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/09 14:22:08 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_reset_terminal(int flag)
{
	static struct termios	term;

	if (!flag)
	{
		if (tcgetattr(STDIN_FILENO, &term) == -1)
		{
			perror("tcgetattr");
			return ;
		}		
	}
	else
	{
		if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
			perror("tcsetattr");		
	}
}
