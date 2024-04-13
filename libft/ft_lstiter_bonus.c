/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:39:23 by shamdoun          #+#    #+#             */
/*   Updated: 2023/11/11 13:18:07 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*head;

	head = lst;
	while (head)
	{
		f(head->content);
		head = head -> next;
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
