/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 20:03:49 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/24 12:23:50 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_getenv(char *name, char **env)
{
	char	**split;
	char	*found;

	while (*env)
	{
		split = ft_split_1(*env, '=');
		if (!split)
			exit (1);
		if (!ft_strncmp(split[0], name, ft_strlen(name) + 1))
		{
			found = ft_strdup(split[1]);
			if (!found)
				exit (1);
			return (found);
		}
		env++;
	}
	return (NULL);
}

void	update_cwd(char *cwd, t_arg *path, char *old_cwd)
{
	char	**split_cwd;
	char	**split_path;
	char	*joined;	
	int		i;
	
	if (check_path(path, cwd))
		return ;
	if (split_values(&split_cwd, &split_path, cwd, path))
		return ;
	joined = ft_strdup("/");
	if (!joined)
		return ;
	copy_old_cwd(old_cwd, split_cwd);
	i = copy_common_path(&joined, split_cwd,
			split_path[0]);
	copy_unique_path(&joined, split_cwd, split_path, i);
	ft_strcpy(cwd, joined);
	free(joined);
}

int	change_to_default_home(t_shell *shell, char **env, int *rv)
{
	char	*home;

	home = ft_getenv("HOME", env);
	if (!home)
	{
		(write(2, "bash: cd: HOME not set\n", 23), add_new_status(shell, 1));
		return (1);
	}
	*rv = chdir(home);
	// add_a_data_to_list(shell, home);
	return (0);
}

void	change_directory(t_arg *path, t_shell *shell, char ***env)
{
	int			return_value;
	char		*gcw_result;
	char		*old_cwd;

	return_value = 0;
	old_cwd = ft_strdup(shell->cwd);
	if (!old_cwd)
	{
		add_new_status(shell, 1);
		return ;
	}
	if (path && ft_strncmp(path->arg, "~", 2))
		return_value = chdir(path->arg);
	else if (change_to_default_home(shell, *env, &return_value))
			return ;
	if (return_value)
	{
		(add_new_status(shell, 1), perror("bash: cd"));
		return ;
	}
	gcw_result = getcwd(shell->cwd, sizeof(shell->cwd));
	if (gcw_result)
	{
		update_oldpwd(old_cwd, shell);
		if (!return_value && path)
			update_cwd(shell->cwd, path, old_cwd);
	}
	else
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
		// char *tmp = old_cwd;
		old_cwd = ft_strjoin(old_cwd, "/..");
		if (!old_cwd)
			return ;
		// add_a_data_to_list(shell, old_cwd);
		ft_strcpy(shell->cwd, old_cwd);
		// free(tmp);
	}
}
