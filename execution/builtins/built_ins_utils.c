/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:50:11 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/22 15:45:03 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*extract_command(char *s, char **env_list, char *command)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env_list[i])
	{
		tmp = ft_strjoin(env_list[i], "/");
		if (!tmp)
			return (NULL);
		command = ft_strjoin(tmp, s);
		free(tmp);
		if (!command)
		{
			free_array(env_list);
			return (NULL);
		}
		if (access(command, F_OK | X_OK) == 0)
		{
			free_array(env_list);
			return (command);
		}
		free(command);
		command = NULL;
		i++;
	}
	return (NULL);
}

char	*find_command_path(char *s, t_shell *shell)
{
	char	**env_list;
	char	*command;
	char	*path;
	
	command = NULL;
	env_list = NULL;
	if (access(s, F_OK | X_OK) == 0)
	{
		command = ft_strdup1(s);
		return (command);
	}
	if (shell->r_path)
		env_list = ft_split_1(shell->r_path, ':');
	else
	{
		path = ft_getenv("PATH", shell->env);
		if (!path)
			return (NULL);
		add_a_data_to_list(shell, path);
		env_list = ft_split_1(path, ':');
	}
	if (!env_list)
		return (NULL);
	int i = 0;
	return (extract_command(s, env_list, command));
}

void	copy_list_updating(char *env_name, char *data,
	t_shell *shell, char **new_environ)
{
	char	**old_list;
	char	**p;
	int		i;

	i = 0;
	old_list = shell->env;
	while (i < list_len(old_list))
	{
		p = ft_split_1(old_list[i], '=');
		if (!p)
			return ;
		if (ft_strncmp(env_name, p[0], ft_strlen(p[0]) + 1))
			ft_memcpy(new_environ, &old_list[i], sizeof(char *));
		else
		{
			data = ft_strdup(data);
			if (!data)
				return ;
			ft_lst_add_ad_back(&shell->all_allocated_data, ft_lstnew_ad(data));
			ft_memcpy(new_environ, &data, sizeof(char *));
		}
		new_environ++;
		free_array(p);
		i++;
	}
	*new_environ = NULL;
}

int	list_len(char **list)
{
	int	i;

	i = 0;
	while (list[i])
		i++;
	return (i);
}

void	add_a_data_to_list(t_shell *shell, void *address)
{
	t_a_data	*new;

	new = ft_lstnew_ad(address);
	if (!new)
		return ;
	ft_lst_add_ad_back(&shell->all_allocated_data, new);
}
