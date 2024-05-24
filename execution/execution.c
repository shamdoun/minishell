/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:57:57 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/24 20:38:20 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern volatile sig_atomic_t	g_signal;

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

void	run_options_path(t_shell *shell, char *command, int mode)
{
	if (!ft_strncmp(command, "env", 4))
	{
		update_env_path_var(shell, "env", 1);
		if (print_all_env_vars(shell->env, shell->all_input))
			return ;
		add_new_status(shell, 0);
	}
	else if (!ft_strncmp(command, "pwd", 4))
		(printf("%s\n", shell->cwd), add_new_status(shell, 0));
	else if (!ft_strncmp(command, "cd", 3))
		change_directory(shell->all_input->args, shell, &shell->env);
	else if (!ft_strncmp(command, "export", 7))
		add_update_env(shell->all_input->args, shell, &shell->env, 1);
	else if (!ft_strncmp(command, "unset", 6))
		remove_env(shell->all_input->args, shell, &shell->env, 1);
	else if (!ft_strncmp(command, "echo", 5))
		echo_message(shell->all_input->args, shell);
	else if (!ft_strncmp(command, "exit", 5))
		exit_shell(shell, shell->all_input->args, mode);
	else
		execute_other_commands(shell, mode);
}

char *ft_last_arg(char *command, t_arg *args)
{
	char	*tmp;

	tmp = NULL;
	if (!args)
		return (command);
	while (args)
	{
		if (args->arg)
			tmp = args->arg;
		args = args->next;
	}
	if (!tmp)
		return (command);
	return (tmp); 
}

void	run_options(t_shell *shell, char *command, int mode)
{
	char *path_env;

	path_env = ft_getenv("PATH", shell->env);
	if ((path_env && !shell->r_path) || (!path_env && shell->r_path))
		run_options_path(shell, command, mode);
	else if (!ft_strncmp(command, "pwd", 4))
		(printf("%s\n", shell->cwd), add_new_status(shell, 0));
	else if (!ft_strncmp(command, "cd", 3))
		change_directory(shell->all_input->args, shell, &shell->env);
	else if (!ft_strncmp(command, "export", 7))
		add_update_env(shell->all_input->args, shell, &shell->env, 1);
	else if (!ft_strncmp(command, "unset", 6))
		remove_env(shell->all_input->args, shell, &shell->env, 1);
	else if (!ft_strncmp(command, "echo", 5))
		echo_message(shell->all_input->args, shell);
	else if (!ft_strncmp(command, "exit", 5))
		exit_shell(shell, shell->all_input->args, mode);
	else
	{
		add_new_status(shell, 127);
		printf("minishell: %s: No such file or directory\n", command);
	}
	if (mode)
		update_env_path_var(shell, ft_last_arg(command, shell->all_input->args), 0);
}

void	open_output_files(t_shell *shell)
{
	t_file *head;

	head = shell->all_input->all_files;
	while (shell->all_input->all_files)
	{
		if (shell->all_input->all_files->type < 3
			&& shell->all_input->out_file > 1)
			close(shell->all_input->out_file);
		if (shell->all_input->all_files->type == 1)
			shell->all_input->out_file
				= open(shell->all_input->all_files->file_name,
					O_WRONLY | O_CREAT | O_TRUNC, 0777);
		else if (shell->all_input->all_files->type == 2)
			shell->all_input->out_file
				= open(shell->all_input->all_files->file_name,
					O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (shell->all_input->out_file < 0)
		{
			perror("failed to open output file!"), add_new_status(shell, 1);
			return ;
		}
		shell->all_input->all_files = shell->all_input->all_files->next;
	}
	if (head)
		shell->all_input->all_files = head;
}

void	run_built_ins(t_shell *shell, int mode)
{
	char	*command;
	
	if (open_input_files(shell))
		return ;
	open_output_files(shell);
	if (redirect_streams(shell))
		return ;
	if (!shell->all_input->command_name)
		return ;
	command = ft_strdup(shell->all_input->command_name);
	if (!command)
	{
		add_new_status(shell, 1);
		return ;
	}
	run_options(shell, command, mode);
	if (shell->all_input->in_file)
		close(shell->all_input->in_file);
	if (shell->all_input->out_file)
		close(shell->all_input->out_file);
	if (!mode)
		exit(ft_last_status(shell->all_status));
}

void	execute_input(t_shell *shell)
{
	int	o_in;
	int	o_out;
	int	rv;

	o_in = dup(STDIN_FILENO);
	o_out = dup(STDOUT_FILENO);
	rv = open_here_docs(shell);
	if (rv)
	{
		add_new_status(shell, rv);
		g_signal = 0;
		handle_all_signals(0);
		dup2(o_in, STDIN_FILENO);
		dup2(o_out, STDOUT_FILENO);
		close(o_in);
		close(o_out);
		return ;
	}
	handle_all_signals(0);
	if (!shell->all_input->next)
		run_built_ins(shell, 1);
	else
		pipex(shell, 0);
	if (dup2(o_in, STDIN_FILENO) == -1)
		return ;
	if (dup2(o_out, STDOUT_FILENO) == -1)
		return ;
	close(o_in);
	close(o_out);
}
