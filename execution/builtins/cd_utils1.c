/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:19:10 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/13 21:38:08 by shamdoun         ###   ########.fr       */
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
