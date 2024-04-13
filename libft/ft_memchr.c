/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:59:14 by shamdoun          #+#    #+#             */
/*   Updated: 2024/01/14 00:24:07 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	value;
	char			*str;

	value = (unsigned char) c;
	str = (char *)s;
	while (n)
	{
		if ((unsigned char)*str == value)
			return ((void *)str);
		str++;
		n--;
	}
	return (0);
}
