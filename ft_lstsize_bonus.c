/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:31:48 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/17 20:42:08 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize(t_list *lst)
{
	int		len;
	t_list	*head;

	head = lst;
	len = 0;
	while (head)
	{
		len++;
		head = head -> next;
	}
	return (len);
}

// #include <stdio.h>
// int main()
// {
// 	t_list *l = NULL;
// 	ft_lstadd_back(&l,ft_lstnew(ft_strdup("heldsdslo")));
// 	//ft_lstadd_back(&l,ft_lstnew(ft_strdup("hello")));
// 	printf("%d",ft_lstsize(l));
// }