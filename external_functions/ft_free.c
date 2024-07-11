/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:41:57 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/11 12:17:36 by aessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(char **ptr, int last)
{
	while (--last >= 0)
		free(*ptr);
	free(ptr);
}

void	ft_free_split(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	free_fail(t_parse_list **list)
{
	while ((*list))
	{
		free(*list);
		(*list) = (*list)->next;
	}
}

void	ft_free_inputlist(t_parse_list **input_list)
{
	while ((*input_list))
	{
		free((*input_list));
		(*input_list) = (*input_list)->next;
	}
}

void	free_list(t_commands *list)
{
	while (list)
	{
		free(list->command);
		free(list);
		list = list->next;
	}
}
