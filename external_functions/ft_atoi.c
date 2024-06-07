/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:41:49 by shamdoun          #+#    #+#             */
/*   Updated: 2024/06/07 15:51:27 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	o_return(int sign)
{
	if (sign < 0)
		return (0);
	return (-1);
}

unsigned char	*remove_spaces(unsigned char *s)
{
	while (*s == ' ' || *s == '\t'
		|| *s == '\n' || *s == '\r'
		|| *s == '\v' || *s == '\f')
		s++;
	return (s);
}

int	return_error_status(void)
{
	ft_putendl_fd("minishell: exit: numeric argument required", 2);
	return (255);
}

int	ft_atoi(const char *str)
{
	int				sign;
	long			result;
	unsigned char	*s;

	s = (unsigned char *)str;
	result = 0;
	sign = 1;
	s = remove_spaces(s);
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign *= -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		if (result > 922337203685477580
			|| ((result == 922337203685477580) && (*s > '7')))
			return (return_error_status());
		result = (result * 10) + (*s - '0');
		s++;
	}
	if (*s)
		return (return_error_status());
	return ((int)result * sign);
}
