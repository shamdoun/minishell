/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:31:38 by shamdoun          #+#    #+#             */
/*   Updated: 2024/01/14 00:23:54 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

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
			return (o_return(sign));
		result = (result * 10) + (*s - '0');
		s++;
	}
	return ((int)result * sign);
}
