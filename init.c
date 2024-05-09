/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:50:55 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/09 19:04:07 by shamdoun         ###   ########.fr       */
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

void	init(t_shell **minishell, char **env)
{
	char	*var;

	(*minishell) = malloc(sizeof(t_shell));
	if ((*minishell) < 0)
		exit(1);
	(*minishell)->all_allocated_data = NULL;
	(*minishell)->all_status = NULL;
	(*minishell)->all_input = NULL;
	(*minishell)->env = env;
	(*minishell)->r_path = NULL;
	getcwd((*minishell)->cwd, sizeof((*minishell)->cwd));
	if (!(*env))
		add_default_env(*minishell);
	else
		update_inhereted_env(*minishell, env);
	var = ft_getenv("_", env);
	add_a_data_to_list(*minishell, var);
	if (!var || ft_strncmp(var, "/usr/bin/env", 13))
		update_env_path_var(*minishell);
	ft_hide_ctrl_c();
}
