/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:19:10 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/09 20:21:26 by shamdoun         ###   ########.fr       */
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
