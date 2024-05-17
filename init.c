/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:50:55 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/16 22:03:24 by shamdoun         ###   ########.fr       */
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

void	init(t_shell **minishell, char **env, int last_exit)
{
	char	*var;

	(*minishell) = malloc(sizeof(t_shell));
	if ((*minishell) < 0)
		return ;
	(*minishell)->all_allocated_data = NULL;
	(*minishell)->all_status = ft_lstnew_status(last_exit);
	(*minishell)->all_input = NULL;
	(*minishell)->env = env;
	(*minishell)->r_path = NULL;
	getcwd((*minishell)->cwd, sizeof((*minishell)->cwd));
	if (!(*env))
		add_default_env(*minishell);
	else
		update_inhereted_env(*minishell);
	var = ft_getenv("_", env);
	add_a_data_to_list(*minishell, var);
	if (!var || ft_strncmp(var, "/usr/bin/env", 13))
		update_env_path_var(*minishell);
	ft_hide_ctrl_c();
}
