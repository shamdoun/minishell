/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:29:42 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/22 11:18:01 by aessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*head;

	if (!lst || !new)
		return ;
	head = *lst;
	if (!head)
		*lst = new;
	else
	{
		while (head -> next)
			head = head -> next;
		head -> next = new;
	}
}
