/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:29:42 by shamdoun          #+#    #+#             */
/*   Updated: 2023/11/08 15:37:36 by shamdoun         ###   ########.fr       */
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

// #include <stdio.h>
// int main()
// {
// 	t_list *l = NULL;
// 	ft_lstadd_back(&l,ft_lstnew(ft_strdup("heldsdslo")));
// 	ft_lstadd_back(&l,ft_lstnew(ft_strdup("hello")));
// 	while (l)
// 	{
// 		printf("%s\n",l->content);
// 		l = l -> next;
// 	}
// }
