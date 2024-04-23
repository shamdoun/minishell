#include "execution.h"

static void run_built_ins(t_shell *shell)
{
    char **args_list;
    if (shell->all_input->all_files)
        printf("open all files!\n");
    if (!ft_strncmp(shell->all_input->command_name, "cd", ft_strlen(shell->all_input->command_name)))
        change_directory(shell->all_input->args, shell, &shell->env);
    else if (!ft_strncmp(shell->all_input->command_name, "export", ft_strlen(shell->all_input->command_name)))
        add_update_env(shell->all_input->args, shell, &shell->env);
    else if(!ft_strncmp(shell->all_input->command_name, "unset", ft_strlen(shell->all_input->command_name)))
        remove_env(shell->all_input->args, shell, &shell->env);
    else if (!ft_strncmp(shell->all_input->command_name, "exit", ft_strlen(shell->all_input->command_name)))
        exit_shell(shell,  shell->all_input->args);
    else if (!ft_strncmp(shell->all_input->command_name, "echo", ft_strlen(shell->all_input->command_name)))
        echo_message(&args_list[1]);
    else if (!ft_strncmp(shell->all_input->command_name, "env", ft_strlen(shell->all_input->command_name)))
        print_all_env_vars(shell->env);
    else if (!ft_strncmp(shell->all_input->command_name, "pwd", ft_strlen(shell->all_input->command_name)))
        printf("%s\n", shell->all_input->cwd);
    else
        execute_binary(args_list, shell, &shell->env);
    free_array(args_list);
}

void execute_input(t_shell *shell)
{
    if (!shell->all_input->next)
        run_built_ins(shell);
}