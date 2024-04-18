/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:38:29 by shamdoun          #+#    #+#             */
/*   Updated: 2024/04/17 18:09:59 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_status	*ft_lstlast(t_status *lst)
{
	t_status	*head;

	head = lst;
	while (head && head -> next)
		head = head -> next;
	return (head);
}
