/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:22:06 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/09 20:24:46 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

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
	t_status	*status;

	new_environ = malloc(sizeof(char *) * (list_len(*env) + 1));
	if (new_environ)
	{
		copy_list_updating(env_name, data, shell, new_environ);
		// add_a_data_to_list(shell, new_environ);
		*env = new_environ;
	}
	else
	{
		status = ft_lstnew_status(errno);
		if (!status)
			exit(1);
		ft_lst_add_status_back(&shell->all_status, status, shell);
	}
}

void	add_env(char *data, t_shell *shell, char ***env)
{
	char		**new_environ;
	char		*new_data;
	t_status	*status;

	new_environ = malloc(sizeof(char *) * (list_len(*env) + 2));
	if (new_environ)
	{
		ft_memcpy(new_environ, *env, list_len(*env) * sizeof(char *));
		new_data = ft_strdup(data);
		if (!new_data)
			exit(1);
		new_environ[list_len(*env)] = new_data;
		new_environ[list_len(*env) + 1] = NULL;
		*env = new_environ;
		add_a_data_to_list(shell, new_data);
		// add_a_data_to_list(shell, new_environ);
	}
	else
	{
		status = ft_lstnew_status(errno);
		if (!status)
			exit(1);
		ft_lst_add_status_back(&shell->all_status, status, shell);
	}
}

void	add_update_env(t_arg *data, t_shell *shell, char ***env)
{
	char	**split_env;

	if (!data)
	{
		declare_all_envs(*env);
		return ;
	}
	if (!ft_strrchr(data->arg, '='))
		return ;
	split_env = ft_split_1(data->arg, '=');
	if (!split_env)
		exit(1);
	if (env_exists(split_env[0], *env))
		update_env(split_env[0], shell, data->arg, env);
	else
		add_env(data->arg, shell, env);
	free_array(split_env);
}
