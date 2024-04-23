/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:32:04 by shamdoun          #+#    #+#             */
/*   Updated: 2024/04/23 16:24:47 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*copy;
	int		len;

	len = ft_strlen(s1);
	copy = malloc(len + 1);
	if (copy)
	{
		ft_memmove(copy, s1, len);
		copy[len] = '\0';
	}
	return (copy);
}
