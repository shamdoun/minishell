/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:22:06 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/24 16:29:11 by shamdoun         ###   ########.fr       */
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
			// free_array(split);
			return (1);
		}
		// free_array(split);
		env++;
	}
	return (0);
}

void	update_env(char *env_name, char *env_value, t_shell *shell, char *data, char ***env)
{
	char		**new_environ;

	(void)env_value;
	new_environ = ft_malloc(sizeof(char *) * (list_len(*env) + 1), 2);
	if (!new_environ)
		add_new_status(shell, errno);
	else
	{
		copy_list_updating(env_name, data, shell, new_environ);
		// add_a_data_to_list(shell, new_environ);
		*env = new_environ;
	}
}

char	*append_env(char *data)
{
	char	*name;
	char	*value;
	char	*result;
	
	name = ft_substr(data, 0, ft_strchr_index(data, '+'));
	if (!name)
		return (NULL);
	value = ft_strchr_occurence(data, '+') + 2;
	result = ft_strjoin(name, "=");
	if (!result)
		return (NULL);
	result = ft_strjoin(result, value);
	return (result);
}

void	add_env(char *data, t_shell *shell, char ***env)
{
	char		**new_environ;
	char		*new_data;

	if (ft_strchr(data, '+'))
		new_data = append_env(data);
	else
		new_data = ft_strdup(data);
	if (!new_data)
		return ;
	new_environ = ft_malloc(sizeof(char *) * (list_len(*env) + 2), 2);
	if (!new_environ)
		add_new_status(shell, errno);
	else
	{
		ft_memcpy(new_environ, *env, list_len(*env) * sizeof(char *));
		new_environ[list_len(*env)] = new_data;
		new_environ[list_len(*env) + 1] = NULL;
		*env = new_environ;
	}
}

int	empty_args(t_arg *data)
{
	while (data)
	{
		if (data->arg)
			return (0);
		data = data->next;
	}
	return (1);
}

int eu_syntax_error(char *data, int mode)
{
	int	i;
	i = 0;
	if (data[i] != '_' && !ft_isalpha(data[i]))
		return (1);
	i++;
	while (data[i] && data[i + 1])
	{
		if (!mode && data[i] == '+' && data[i + 1] != '=')
			return (1);
		else if (mode && !ft_isalpha(data[i]) && !ft_isdigit(data[i]))
			return (1);
		i++;
	}
	if (data[i])
	{
		if (!mode && data[i] != '_' && data[i] != '=' && !ft_isalpha(data[i]) && !ft_isdigit(data[i]))
			return (1);
		else if (mode && data[i] != '_' && !ft_isalpha(data[i]) && !ft_isdigit(data[i]))
			return (1);
	}
	return (0);
}

void	add_update_env(t_arg *data, t_shell *shell, char ***env, int mode)
{
	char	**split_env;
	bool	error;

	error = false;
	if (!data || empty_args(data))
	{
		(declare_all_envs(*env), add_new_status(shell, 0));
		return ;
	}
	while (data && data->arg)
	{
		if (eu_syntax_error(data->arg, 0))
			(write(2, "export: not a valid identifier\n", 31), add_new_status(shell, 1), error = true);
		else
		{
			// if (ft_strrchr(data->arg, '='))
			// {
				if (ft_strchr(data->arg, '+'))
					split_env = ft_split_1(data->arg, '+');
				else
					split_env = ft_split_1(data->arg, '=');
				if (!split_env)
				{
					add_new_status(shell, 1);
					return ;
				}
				if (env_exists(split_env[0], *env))
					update_env(split_env[0], split_env[1], shell, data->arg, env);
				else
					add_env(data->arg, shell, env);
				// free_array(split_env);
			// }
			if (!error && mode)
				add_new_status(shell, 0);
		}
		data = data->next;
	}
}
