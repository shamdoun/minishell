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

void run_built_ins(t_shell *shell)
{
	redirect_streams(shell);
    if (!ft_strncmp(shell->all_input->command_name, "cd", 3))
        change_directory(shell->all_input->args, shell, &shell->env);
    else if (!ft_strncmp(shell->all_input->command_name, "export", 7))
        add_update_env(shell->all_input->args, shell, &shell->env);
	else if(!ft_strncmp(shell->all_input->command_name, "unset", 6))
        remove_env(shell->all_input->args, shell, &shell->env);
    else if (!ft_strncmp(shell->all_input->command_name, "exit", 5))
        exit_shell(shell, shell->all_input->args);
	else if (!ft_strncmp(shell->all_input->command_name, "echo", 5))
        echo_message(shell->all_input->args);
    else if (!ft_strncmp(shell->all_input->command_name, "env", 4))
        print_all_env_vars(shell->env);
    else if (!ft_strncmp(shell->all_input->command_name, "pwd", 4))
        printf("%s\n", shell->cwd);
    else
        execute_binary(shell);
}

void execute_input(t_shell *shell)
{
	int o_in;
	int o_out;
	o_in = dup(STDIN_FILENO);
	o_out = dup(STDOUT_FILENO);
	open_input_files(shell);
    if (!shell->all_input->next)
        run_built_ins(shell);
	else
		pipex(shell);
	dup2(o_in, STDIN_FILENO);
	dup2(o_out, STDOUT_FILENO);
}