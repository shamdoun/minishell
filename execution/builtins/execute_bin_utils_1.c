/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin_utils_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 20:55:46 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/11 21:08:51 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	bin_exists(char *s)
{
	int	a;
	int	b;
	int	c;
	int	d;

	a = !ft_strncmp(s, "/bin/", 5) && s[6];
	b = !ft_strncmp(s, "/usr/bin/", 9) && s[10];
	c = !ft_strncmp(s, "/sbin/", 6) && s[7];
	d = !ft_strncmp(s, "/usr/sbin/", 10) && s[11];
	return (a || b || c);
}

int	incorrect_syntax(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '/' && s[i + 1] && s[i + 1] == '/')
			return (1);
		i++;
	}
	return (0);
}
