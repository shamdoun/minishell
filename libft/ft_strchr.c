/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:33:14 by shamdoun          #+#    #+#             */
/*   Updated: 2023/11/05 21:34:53 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	value;
	int		i;

	value = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == value)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == value)
		return ((char *)(s + i));
	return (NULL);
}
