/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:39:56 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/11 21:50:57 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// extern volatile sig_atomic_t	g_signal;

void	reset_resources(t_shell *shell, int rv, int o_in, int o_out)
{
	add_new_status(shell, rv);
	g_signal = 0;
	handle_all_signals(0);
	dup2(o_in, STDIN_FILENO);
	dup2(o_out, STDOUT_FILENO);
	close(o_in);
	close(o_out);
}

int	open_output_files(t_shell *shell)
{
	if (shell->all_input->out_file > 1)
		close(shell->all_input->out_file);
	if (shell->all_input->all_files->type == 1)
		shell->all_input->out_file
			= open(shell->all_input->all_files->file_name,
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (shell->all_input->all_files->type == 2)
		shell->all_input->out_file
			= open(shell->all_input->all_files->file_name,
				O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (shell->all_input->out_file < 0)
	{
		perror("failed to open output file!");
		add_new_status(shell, 1);
		return (1);
	}
	return (0);
}

int	open_files(t_shell *shell)
{
	while (shell->all_input->all_files)
	{
		if (shell->all_input->all_files->type >= 3 && open_input_files(shell))
			return (1);
		if (open_output_files(shell))
			return (1);
		shell->all_input->all_files = shell->all_input->all_files->next;
	}
	return (0);
}

int	run_special_cases(t_shell *shell, char *command)
{
	if (!ft_strncmp(command, ".", 2)
		&& (!shell->all_input->args || empty_args(shell->all_input->args)))
	{
		ft_putendl_fd(POINT_INPUT, 2);
		add_new_status(shell, 2);
		return (1);
	}
	else if (!ft_strncmp(command, ".", 2))
	{
		ft_putendl_fd("minishell: .: No such file or directoty", 2);
		add_new_status(shell, 1);
		return (1);
	}
	return (0);
}

void	update_args(t_shell *shell)
{
	char	**test;
	int		i;

	i = 0;
	test = ft_split_1(shell->all_input->command_name, ' ');
	while (test && test[i])
		i++;
	if (i >= 1 && shell->is_expanded)
	{
		shell->all_input->command_name = test[0];
		while (--i > 0)
			ft_lstadd_front(&(shell->all_input->args), test[i]);
	}
}
