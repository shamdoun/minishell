/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:25:11 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/17 21:39:59 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_join_args(t_arg *args)
{
	char	*result;
	char	*tmp;

	result = NULL;
	result = ft_strdup(args->arg);
	if (!result)
		exit (1);
	args = args->next;
	while (args)
	{
		tmp = ft_strjoin(" ", args->arg);
		if (!tmp)
			perror("failed to join:");
		result = ft_strjoin(result, tmp);
		args = args->next;
	}
	return (result);
}

int	is_flag(char *split)
{
	if (*split == '-' && *(split + 1))
	{
		split++;
		while (*split)
		{
			if (*split != 'n')
				return (0);
			split++;
		}
		return (1);
	}
	return (0);
}

void	print_message(t_arg *split, bool *new_line)
{
	while (split && is_flag(split->arg))
	{
		*new_line = false;
		split = split->next;
	}
	while (split)
	{
		printf("%s", split->arg);
		if (split->next)
			printf(" ");
		split = split->next;
	}
}

void	echo_message(t_arg *args, t_shell *shell)
{
	bool	new_line;
	// char	*joined_args;
	// char	**split;

	new_line = true;
	if (!args)
	{
		printf("\n"), add_new_status(shell, 0);
		return ;
	}
	// joined_args = ft_join_args(args);
	// if (!joined_args)
	// 	exit(1);
	// split = ft_split_1(joined_args, ' ');
	// if (!split)
	// {
	// 	add_new_status(shell, 1);
	// 	return ;
	// }
	print_message(args, &new_line);
	if (new_line)
		printf("\n");
	// free_array(split);
	// free(joined_args), 
	add_new_status(shell, 0);
}
