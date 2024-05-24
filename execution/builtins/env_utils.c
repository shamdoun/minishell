/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:54:01 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/24 17:17:13 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*retrieve_value(t_shell *shell)
{
	char	*var;
	int		new_value;

	var = ft_getenv("SHLVL", shell->env);
	if (!var)
	{
		perror("failed!");
		return (NULL);
	}
	// add_a_data_to_list(shell, var);
	new_value = ft_atoi(var) + 1;
	if (new_value == 1000)
	{
		return (ft_strdup(""));
	}
	else
		return (ft_itoa_v2(new_value));
}

void	update_shlvl(t_shell *shell)
{
	t_arg	*new_shlvl;
	char	*tmp;

	tmp = retrieve_value(shell);
	if (!tmp)
	{
		perror("failed!");
		return ;
	}
	new_shlvl = ft_malloc(sizeof(t_arg), 0);
	if (!new_shlvl)
		return ;
	new_shlvl->arg = ft_strjoin("SHLVL=", tmp);
	if (!new_shlvl->arg)
		return ;
	new_shlvl->next = NULL;
	// add_a_data_to_list(shell, new_shlvl->arg);
	add_update_env(new_shlvl, shell, &shell->env, 0);
	// free(new_shlvl);
	// free(tmp);
}
