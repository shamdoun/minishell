/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 22:08:59 by shamdoun          #+#    #+#             */
/*   Updated: 2024/01/14 00:21:30 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 9
# endif

char	*get_next_line(int fd);
int		ft_strchr1(char *str, char c);
char	*ft_update_buffer(char *b);
char	*ft_add_data(char *data, char *buffer, int fd);
char	*ft_strdup1(char *s);
char	*ft_strjoin1(char *s1, char *s2);
void	*ft_memcpy1(char *dst, char *src, int size);
size_t	ft_strlen1(char *str);
void	ft_cpy_cat(char *dst, char *s1, char *s2);
#endif
