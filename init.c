/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:50:55 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/22 20:17:28 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_hide_ctrl_c(void)
{
	struct termios	ter;

	tcgetattr(STDIN_FILENO, &ter);
	ter.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &ter);
}

void ft_recover_echo(void)
{
	struct termios	ter;

	tcgetattr(STDIN_FILENO, &ter);
	ter.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &ter);
}

int	init_shell_struct(t_shell **minishell, char **env, int last_exit, char *cwd)
{
	(*minishell) = ft_malloc(sizeof(t_shell), 0);
	if (!(*minishell))
	{
		printf("is NULL");
		return (1);
	}
	(*minishell)->all_allocated_data = NULL;
	(*minishell)->all_status = ft_lstnew_status(last_exit);
	// add_a_data_to_list(*minishell, (*minishell)->all_status);
	if (!cwd)
		getcwd((*minishell)->cwd, sizeof((*minishell)->cwd));
	else
		ft_strcpy((*minishell)->cwd, cwd);
	(*minishell)->all_input = NULL;
	(*minishell)->env = env;
	return (0);
}

void	init_shell_environment(t_shell **minishell, int *is_new_shell, char *inherited_r_path)
{
	char	*var;
	
	var = ft_getenv("PATH", (*minishell)->env);
	if (*is_new_shell && !var)
		(*minishell)->r_path = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	else
		(*minishell)->r_path = inherited_r_path;
	// free(var);
	// var = NULL;
	if (!(*((*minishell)->env)))
		add_default_env(*minishell);
	else
		update_inhereted_env(*minishell, is_new_shell);
	var = ft_getenv("_", (*minishell)->env);
	// add_a_data_to_list(*minishell, var);
	if (!var || ft_strncmp(var, "/usr/bin/env", 13))
		update_env_path_var(*minishell);
	if (*is_new_shell == 1)
		*is_new_shell = 0;
	ft_hide_ctrl_c();
}

void	init(t_shell **minishell, char **env, int last_exit, int *is_new_shell, char *inherited_r_path)
{
	char	*var;

	(*minishell) = malloc(sizeof(t_shell));
	if ((*minishell) < 0)
		return ;
	(*minishell)->all_allocated_data = NULL;
	(*minishell)->all_status = ft_lstnew_status(last_exit);
	add_a_data_to_list(*minishell, (*minishell)->all_status);
	(*minishell)->all_input = NULL;
	(*minishell)->env = env;
	if (*is_new_shell)
	{
		(*minishell)->r_path = NULL;
		printf("Set r_path to null\n");
	}
	else
		(*minishell)->r_path = inherited_r_path;
	getcwd((*minishell)->cwd, sizeof((*minishell)->cwd));
	if (!(*env))
		add_default_env(*minishell);
	else
		update_inhereted_env(*minishell, is_new_shell);
	if (*is_new_shell == 1)
		*is_new_shell = 0;
	var = ft_getenv("_", env);
	add_a_data_to_list(*minishell, var);
	if (!var || ft_strncmp(var, "/usr/bin/env", 13))
		update_env_path_var(*minishell);
	ft_hide_ctrl_c();
}
