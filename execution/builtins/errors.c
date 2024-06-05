/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:08:03 by shamdoun          #+#    #+#             */
/*   Updated: 2024/06/05 21:19:10 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error_status_update(char *error, t_shell *shell, int s)
{
	if (error)
		ft_putstr_fd(error, 2);
	add_new_status(shell, s);
}

void	error_arg_status_update(char *error, char *arg, t_shell *shell, int s)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error, 2);
	add_new_status(shell, s);
}
