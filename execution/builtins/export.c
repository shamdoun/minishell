/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:22:06 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/22 15:38:33 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	env_exists(char *name, char **env)
{
	char	**split;

	while (*env)
	{
		split = ft_split_1(*env, '=');
		if (!ft_strncmp(split[0], name, ft_strlen(split[0]) + 1))
		{
			free_array(split);
			return (1);
		}
		free_array(split);
		env++;
	}
	return (0);
}

void	update_env(char *env_name, t_shell *shell, char *data, char ***env)
{
	char		**new_environ;
	
	new_environ = malloc(sizeof(char *) * (list_len(*env) + 1));
	if (!new_environ)
		add_new_status(shell, errno);
	else
	{
		copy_list_updating(env_name, data, shell, new_environ);
		add_a_data_to_list(shell, new_environ);
		*env = new_environ;
	}
}

void	add_env(char *data, t_shell *shell, char ***env)
{
	char		**new_environ;
	char		*new_data;

	new_environ = malloc(sizeof(char *) * (list_len(*env) + 2));
	if (!new_environ)
		add_new_status(shell, errno);
	else
	{
		ft_memcpy(new_environ, *env, list_len(*env) * sizeof(char *));
		new_data = ft_strdup(data);
		if (!new_data)
			return ;
		new_environ[list_len(*env)] = new_data;
		new_environ[list_len(*env) + 1] = NULL;
		*env = new_environ;
		add_a_data_to_list(shell, new_data);
		add_a_data_to_list(shell, new_environ);
	}
}

void	add_update_env(t_arg *data, t_shell *shell, char ***env, int mode)
{
	char	**split_env;
	bool	error;

	error = false;
	if (!data)
	{
		(declare_all_envs(*env), add_new_status(shell, 0));
		return ;
	}
	while (data && data->arg)
	{
		if (*data->arg == '=')
			(write(2, "export: not a valid identifier\n", 31), add_new_status(shell, 1), error = true);
		else
		{
			if (ft_strrchr(data->arg, '='))
			{
				split_env = ft_split_1(data->arg, '=');
				if (!split_env)
				{
					add_new_status(shell, 1);
					return ;
				}
				if (env_exists(split_env[0], *env))
					update_env(split_env[0], shell, data->arg, env);
				else
					add_env(data->arg, shell, env);
				free_array(split_env);
			}
			if (!error && mode)
				add_new_status(shell, 0);
		}
		data = data->next;
	}
}
