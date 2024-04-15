/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 22:08:51 by shamdoun          #+#    #+#             */
/*   Updated: 2024/01/14 00:22:28 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_cpy_cat(char *dst, char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dst[i + j] = s2[j];
		j++;
	}
	dst[i + j] = '\0';
}

char	*ft_add_data(char *data, char *buffer, int fd)
{
	int		read_bits;
	char	*tmp;

	read_bits = read(fd, buffer, BUFFER_SIZE);
	while (read_bits)
	{
		if (read_bits == -1)
			return (NULL);
		buffer[read_bits] = '\0';
		tmp = data;
		data = ft_strjoin1(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr1(buffer, '\n'))
			break ;
		read_bits = read(fd, buffer, BUFFER_SIZE);
	}
	return (data);
}

char	*ft_update_buffer(char *b)
{
	int		i;
	char	*n;

	i = 0;
	while (b[i] && b[i] != '\n')
		i++;
	if (!b[i] || !b[1])
	{
		return (NULL);
	}
	n = malloc(ft_strlen1(b) - i);
	if (!n)
		return (NULL);
	ft_memcpy1(n, b + i + 1, ft_strlen1(b) - i);
	if (*n == '\0')
	{
		free(n);
		return (NULL);
	}
	b[i + 1] = '\0';
	return (n);
}

char	*get_next_line(int fd)
{
	static char	*all_data;
	char		*buffer;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(all_data), all_data = NULL, NULL);
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!(buffer))
		return (NULL);
	result = ft_add_data(all_data, buffer, fd);
	free(buffer);
	buffer = NULL;
	if (!result)
	{
		free(all_data);
		return (NULL);
	}
	all_data = ft_update_buffer(result);
	return (result);
}
