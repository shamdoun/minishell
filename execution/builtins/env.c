/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:45:04 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/22 20:23:34 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	print_all_env_vars(char **env, t_input *input)
{
	int	i;

	if (input->args)
	{
		ft_putstr_fd("env: ", 2);
		// while (input->args)
		// {
		// 	ft_putstr_fd(input->args->arg, 2);
		// 	if (input->args->next)
		// 		ft_putchar_fd(' ', 2);
		// 	input->args = input->args->next;
		// }
		// ft_putchar_fd(':', 2);
		ft_putendl_fd(WRONG_INPUT, 2);
		return (1);
	}
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

void	update_env_path_var(t_shell *shell)
{
	t_arg	*new_envpath;

	new_envpath = ft_malloc(sizeof(t_arg), 0);
	if (!new_envpath)
		perror("failed!");
	new_envpath->arg = ft_strdup("_=/usr/bin/env");
	new_envpath->next = NULL;
	add_update_env(new_envpath, shell, &shell->env, 0);
	// free(new_envpath->arg);
	// free(new_envpath);
}

void	declare_all_envs(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
}

void	add_default_env(t_shell *shell)
{
	t_arg	*tmp;
	char	*pwd;

	tmp = malloc(sizeof(t_arg));
	pwd = ft_strjoin("PWD=", shell->cwd);
	tmp->arg = pwd;
	tmp->next = NULL;
	add_update_env(tmp, shell, &shell->env, 0);
	// free(tmp->arg);
	// tmp->arg = NULL;
	tmp->arg = ft_strdup("SHLVL=1");
	tmp->next = NULL;
	add_update_env(tmp, shell, &shell->env, 0);
	// free(tmp->arg);
	// tmp->arg = NULL;
	free(tmp);
	// shell->r_path = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
}

void	update_inhereted_env(t_shell *shell, int *is_new_shell)
{
	t_arg	*oldpwd;
	
	if (*is_new_shell)
	{
		oldpwd = ft_malloc(sizeof(t_arg), 0);
		oldpwd->arg = ft_strdup("OLDPWD");
		oldpwd->next = NULL;
		remove_env(oldpwd, shell, &shell->env, 0);
		// free(oldpwd->arg);
		// free(oldpwd);
		*is_new_shell = 0;
		update_shlvl(shell);
	}
}
