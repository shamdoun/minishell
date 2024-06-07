/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:40:03 by shamdoun          #+#    #+#             */
/*   Updated: 2024/06/07 15:16:56 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array(char **a)
{
	int	i;

	i = 0;
	while (a[i])
	{
		free(a[i]);
		i++;
	}
	free(a);
}

char	*ft_strdup1(char *s)
{
	char	*r;
	int		i;

	i = 0;
	r = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!r)
		return (NULL);
	while (s[i])
	{
		r[i] = s[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

char	*ft_last_arg(char *command, t_arg *args)
{
	char	*tmp;

	tmp = NULL;
	if (!args)
		return (command);
	while (args)
	{
		if (args->arg)
			tmp = args->arg;
		args = args->next;
	}
	if (!tmp || !ft_strncmp(tmp, "", 1))
		return (command);
	return (tmp);
}

void	ft_lstadd_front(t_arg **lst, char *new)
{
	t_arg	*head;
	t_arg	*arg;

	arg = ft_malloc(sizeof(t_arg), 2);
	if (arg == NULL)
		return ;
	arg->arg = new;
	if (!lst || !arg)
		return ;
	head = (*lst);
	(*lst) = arg;
	(*lst)->next = head;
}
