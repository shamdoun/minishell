/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:25:13 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/11 15:53:53 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_same_value(char *p1, char *p2)
{
	char	*cp1;
	char	*cp2;

	cp1 = ft_strdup(p1);
	cp2 = ft_strdup(p2);
	ft_str_tolower(cp1);
	ft_str_tolower(cp2);
	if (!ft_strncmp(cp1, cp2, ft_strlen(cp2)))
	{
		free(cp1);
		free(cp2);
		return (1);
	}
	free(cp1);
	free(cp2);
	return (0);
}

int	check_path(t_arg *path, char *cwd)
{
	if (!path || !ft_strncmp(path->arg, "~", 2)
		|| !ft_strncmp(path->arg, "..", 3))
		return (1);
	if (ft_same_value(path->arg, cwd))
	{
		strcpy(cwd, path->arg);
		return (1);
	}
	return (0);
}

void	split_values(char ***split_cwd,
	char ***split_path, char *cwd, t_arg *path)
{
	*split_cwd = ft_split_1(cwd, '/');
	if (!(*split_cwd))
		exit(1);
	*split_path = ft_split_1(path->arg, '/');
	if (!(*split_path))
		exit(1);
	while (!ft_strncmp((*split_path)[0], ".", 2)
		|| !ft_strncmp((*split_path)[0], "..", 2))
	{
		free((*split_path)[0]);
		(*split_path)++;
	}
}

int	copy_common_path(char **joined, char **split_cwd, int n)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < n)
	{
		tmp = *joined;
		*joined = ft_strjoin(*joined, split_cwd[i]);
		if (!(*joined))
			exit(1);
		free(tmp);
		tmp = NULL;
		tmp = *joined;
		*joined = ft_strjoin(*joined, "/");
		if (!(*joined))
			exit(1);
		free(tmp);
		tmp = NULL;
		i++;
	}
	return (i);
}

void	copy_unique_path(char **joined, char **split_cwd,
	char **split_path, int i)
{
	int		j;
	char	*tmp;

	j = 0;
	while (split_cwd[i])
	{
		strcpy(split_cwd[i], split_path[j]);
		tmp = *joined;
		*joined = ft_strjoin(*joined, split_cwd[i]);
		if (!(*joined))
			exit(1);
		free(tmp);
		tmp = NULL;
		j++;
		if (split_path[j])
		{
			tmp = *joined;
			*joined = ft_strjoin(*joined, "/");
			if (!(*joined))
				exit(1);
			free(tmp);
			tmp = NULL;
		}
		i++;
	}
}
