/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 22:05:17 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/16 21:47:20 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	copy_list_excluding(char **new_environ, char **old_env, char *str)
{
	char	**p;
	int		i;

	i = 0;
	while (i < list_len(old_env))
	{
		p = ft_split_1(old_env[i], '=');
		if (!p)
			return ;
		if (ft_strncmp(str, p[0], ft_strlen(p[0]) + 1))
		{
			ft_memcpy(new_environ, &old_env[i], sizeof(char *));
			new_environ++;
		}
		free_array(p);
		i++;
	}
	*new_environ = NULL;
}

void	remove_env(t_arg *data, t_shell *shell, char ***env, int mode)
{
	char		**new_environ;
	bool		error;

	error = false;
	while (data && data->arg)
	{
		if (ft_strrchr(data->arg, '='))
			(perror("bash: unset: not a valid identifier"), add_new_status(shell, 1), error = true);
		else
		{
			if (!ft_strncmp(data->arg, "PATH", 5) && shell->r_path)
			{
				free(shell->r_path);
				(shell->r_path = NULL);
			}
			else if (env_exists(data->arg, *env))
			{
				new_environ = malloc(sizeof(char *) * (list_len(*env)));
				if (!new_environ)
				{
					add_new_status(shell, 1);
					return ;
				}
				copy_list_excluding(new_environ, *env, data->arg);
				(*env = new_environ);
			}
			if (!error && mode)
				add_new_status(shell, 0);
		}
		data = data->next;
	}
}
