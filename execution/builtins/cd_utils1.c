/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:19:10 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/15 21:46:30 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	copy_old_cwd(char *old_cwd, char **split_cwd)
{
	char	**split_oldcwd;
	int		i;

	i = 0;
	split_oldcwd = ft_split_1(old_cwd, '/');
	if (!split_oldcwd)
		exit(1);
	while (split_cwd[i] && split_oldcwd[i])
	{
		if (ft_same_value(split_cwd[i], split_oldcwd[i]))
			strcpy(split_cwd[i], split_oldcwd[i]);
		i++;
	}
	free_array(split_oldcwd);
}

void	update_cwd_list(char **split_cwd, char **split_path, int k)
{
	int	j;

	j = 0;
	while (split_path[j])
	{
		if (split_cwd[k])
		{
			if (ft_same_value(split_cwd[k], split_path[j]))
			{
				strcpy(split_cwd[k], split_path[j]);
				k++;
			}
			else if (ft_same_value(split_cwd[k - 1], split_path[j]))
				strcpy(split_cwd[k - 1], split_path[j]);
		}
		else
		{
			if (ft_same_value(split_cwd[k - 1], split_path[j]))
				strcpy(split_cwd[k - 1], split_path[j]);
		}
		j++;
	}
}

int	path_is_only_levels(char **split)
{
	while (*split)
	{
		if (ft_strncmp(*split, "..", ft_strlen(*split)))
			return (0);
		split++;
	}
	return (1);
}

void update_oldpwd(char *old_pwd, t_shell *shell)
{
	t_arg	*oldpwd_env;
	char 	*tmp;

	oldpwd_env = malloc(sizeof(t_arg));
	if (!oldpwd_env)
	{
		add_new_status(shell, 1);
		return;
	}
	tmp = ft_strjoin("OLDPWD=", old_pwd);
	if (!tmp)
	{
		add_new_status(shell, 1);
		return ;
	}
	oldpwd_env->arg = tmp;
	oldpwd_env->next = NULL;
	add_update_env(oldpwd_env, shell, &shell->env);
}