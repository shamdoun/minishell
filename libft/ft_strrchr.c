/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:13:35 by shamdoun          #+#    #+#             */
/*   Updated: 2023/11/11 13:10:10 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	value;
	char	*temp;

	value = (char) c;
	temp = NULL;
	while (*s)
	{
		if (*s == value)
		{
			temp = (char *)s;
		}
		s++;
	}
	if (*s == value)
		return ((char *)s);
	if (temp)
		return (temp);
	return (NULL);
}
