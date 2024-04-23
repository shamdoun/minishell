/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:27:01 by shamdoun          #+#    #+#             */
/*   Updated: 2023/11/11 13:11:39 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	len_s;
	size_t	len_d;

	i = 0;
	j = 0;
	len_s = ft_strlen(src);
	if (!dstsize && !dst)
		return (len_s);
	len_d = ft_strlen(dst);
	if (len_d >= dstsize)
		return (len_s + dstsize);
	while (dst[i])
		i++;
	while (src[j] && j < dstsize - len_d - 1)
	{
		dst[i++] = src[j++];
	}
	dst[i] = '\0';
	return (len_s + len_d);
}
