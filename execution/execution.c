#include "execution.h"
extern volatile sig_atomic_t stop_signal;

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

void run_built_ins(t_shell *shell, int mode)
{
	char *command;
	if (open_input_files(shell))
		return ;
	redirect_streams(shell);
	if (!shell->all_input->command_name)
		return ;
	command = ft_strdup(shell->all_input->command_name);
	ft_str_tolower(command);
    if (!ft_strncmp(command, "cd", 3))
        change_directory(shell->all_input->args, shell, &shell->env);
    else if (!ft_strncmp(command, "export", 7))
        add_update_env(shell->all_input->args, shell, &shell->env);
	else if(!ft_strncmp(command, "unset", 6))
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
        execute_binary(shell, mode);
	if (shell->all_input->in_file)
		close(shell->all_input->in_file);
	if (shell->all_input->out_file)
		close(shell->all_input->out_file);
	if (!mode)
		exit(0);
	else
		stop_signal = 0;
	free(command);
}

void execute_input(t_shell *shell)
{
	int o_in;
	int o_out;
	o_in = dup(STDIN_FILENO);
	o_out = dup(STDOUT_FILENO);
	if (open_here_docs(shell))
	{
		dup2(o_in, STDIN_FILENO);
		dup2(o_out, STDOUT_FILENO);
		close(o_in);
		close(o_out);
		return ;
	}
	if (!shell->all_input->next)
        run_built_ins(shell, 1);
	else
		pipex(shell, 0);
	dup2(o_in, STDIN_FILENO);
	dup2(o_out, STDOUT_FILENO);
	close(o_in);
	close(o_out);
}