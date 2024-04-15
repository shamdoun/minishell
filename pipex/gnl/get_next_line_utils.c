/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 22:08:46 by shamdoun          #+#    #+#             */
/*   Updated: 2024/01/14 00:22:13 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen1(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	ft_strchr1(char *b, char c)
{
	while (b && *b)
	{
		if (*b == c)
			return (1);
		b++;
	}
	return (0);
}

void	*ft_memcpy1(char *dst, char *src, int size)
{
	char	*s;
	char	*d;
	int		i;

	i = 0;
	if (dst == src)
		return (dst);
	d = (char *)dst;
	s = (char *)src;
	while (i < size)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}

char	*ft_strdup1(char *s)
{
	char	*r;
	int		i;

	i = 0;
	r = (char *)malloc(sizeof(char) * ft_strlen1(s) + 1);
	if (!r)
		return (NULL);
	while (s[i])
	{
		r[i] = s[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	char	*js;
	size_t	len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup1(s2));
	if (!s2)
		return (ft_strdup1(s1));
	len = ft_strlen1(s1) + ft_strlen1(s2);
	js = malloc(len + 1);
	if (!js)
		return (NULL);
	ft_cpy_cat(js, s1, s2);
	return (js);
}
