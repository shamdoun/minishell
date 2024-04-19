/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:34:17 by shamdoun          #+#    #+#             */
/*   Updated: 2024/04/19 17:02:54 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_status	*ft_lstnew(int content)
{
	t_status	*n_node;

	n_node = (t_status *)malloc(sizeof(t_status));
	if (!n_node)
		return (NULL);
	n_node -> status = content;
	n_node -> next = NULL;
	return (n_node);
}

t_a_data	*ft_lstnew_a_data(void *content)
{
	t_a_data	*n_node;

	n_node = (t_a_data *)malloc(sizeof(t_status));
	if (!n_node)
		return (NULL);
	n_node -> data = content;
	n_node -> next = NULL;
	return (n_node);
}
