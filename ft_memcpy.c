/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:53:56 by shamdoun          #+#    #+#             */
/*   Updated: 2024/04/23 16:24:27 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*s;
	char	*d;
	int		i;

	i = 0;
	s = (char *)src;
	d = (char *)dst;
	if (dst == src)
		return (dst);
	while (n--)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
