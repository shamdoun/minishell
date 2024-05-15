/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:57:57 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/15 10:47:37 by aessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	free_array(char **a)
{
	int	i;

	i = 0;
	while (a[i])
	{
		free(a[i]);
		i++;
	}
	free(a);
}

char	*ft_strdup1(char *s)
{
	char	*r;
	int		i;

	i = 0;
	r = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!r)
		return (NULL);
	while (s[i])
	{
		r[i] = s[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

void	run_options(t_shell *shell, char *command, int mode)
{
	if (!ft_strncmp(command, "cd", 3))
		change_directory(shell->all_input->args, shell, &shell->env);
	else if (!ft_strncmp(command, "export", 7))
		add_update_env(shell->all_input->args, shell, &shell->env);
	else if (!ft_strncmp(command, "unset", 6))
		remove_env(shell->all_input->args, shell, &shell->env);
	else if (!ft_strncmp(command, "exit", 5))
		exit_shell(shell, shell->all_input->args);
	else if (!ft_strncmp(command, "echo", 5))
		echo_message(shell->all_input->args);
	else if (!ft_strncmp(command, "env", 4))
		print_all_env_vars(shell->env);
	else if (!ft_strncmp(command, "pwd", 4))
		printf("%s\n", shell->cwd);
	else
		execute_other_commands(shell, mode);
}

void	run_built_ins(t_shell *shell, int mode)
{
	char	*command;

	if (open_input_files(shell))
		return ;
	redirect_streams(shell);
	if (!shell->all_input->command_name)
		return ;
	command = ft_strdup(shell->all_input->command_name);
	if (!command)
		exit(1);
	add_a_data_to_list(shell, command);
	if (!ft_same_value(command, "exit"))
		ft_str_tolower(command);
	run_options(shell, command, mode);
	if (shell->all_input->in_file)
		close(shell->all_input->in_file);
	if (shell->all_input->out_file)
		close(shell->all_input->out_file);
	if (!mode)
		exit(ft_last_status(shell->all_status));
	free(command);
}

void	execute_input(t_shell *shell)
{
	int	o_in;
	int	o_out;

	o_in = dup(STDIN_FILENO);
	o_out = dup(STDOUT_FILENO);
	if (open_here_docs(shell))
	{
		signal(SIGINT, &handle_signal);
		dup2(o_in, STDIN_FILENO);
		dup2(o_out, STDOUT_FILENO);
		close(o_in);
		close(o_out);
		return ;
	}
	signal(SIGINT, &handle_signal);
	if (shell->all_input->next == NULL)
		run_built_ins(shell, 1);
	else
		pipex(shell, 0);
	dup2(o_in, STDIN_FILENO);
	dup2(o_out, STDOUT_FILENO);
	close(o_in);
	close(o_out);
}
