/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:48:20 by shamdoun          #+#    #+#             */
/*   Updated: 2023/11/05 22:21:06 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	value;
	size_t			i;
	unsigned char	*s;

	s = (unsigned char *)b;
	i = 0;
	value = (unsigned char) c;
	while (i < len)
	{
		s[i] = value;
		i++;
	}
	return (b);
}
