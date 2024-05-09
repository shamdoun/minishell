#include "../execution.h"

extern volatile sig_atomic_t g_stop_signal;

void update_split_list(char ***args_list, char *data)
{
    char **new_list = malloc(sizeof(char *) * (list_len(*args_list) + 2));
    if (!new_list)
        exit(1);
    new_list[0] = ft_strdup(data);
    if (!new_list)
        exit(1);
    ft_memcpy(&new_list[1], *args_list, list_len(*args_list) * sizeof(char *));
    new_list[list_len(*args_list) + 1] = NULL;
    *args_list = new_list;
}

void execute_binary(t_shell *shell, int mode)
{
    char **args_list;
    char *joined_args;
    char *cmd_path;
    int  rv;
    pid_t child;

    if (shell->all_input->args)
    {
        joined_args = ft_join_args(shell->all_input->args);
        if (!joined_args)
            exit(1);
        args_list = ft_split_1(joined_args, ' ');
        if (!args_list)
            exit(1);
        update_split_list(&args_list, shell->all_input->command_name);
    }
    else
    {
        args_list = ft_split_1(shell->all_input->command_name, ' ');
        if (!args_list)
            exit(1);
    }
    cmd_path = find_command_path(args_list[0], shell);
    if (cmd_path)
    {
        if (mode)
        {
            child = fork();
            if (child == 0)
            {
                rv = execve(cmd_path, args_list, shell->env);
                fprintf(stderr, "error of %d\n", errno);
                if (rv)
                    ft_lst_add_status_back(&shell->all_status, ft_lstnew_status(errno), shell);
            }
            int status;
            waitpid(-1, &status, 0);
            ft_lst_add_status_back(&shell->all_status, ft_lstnew_status(status), shell);
        }
        else
        {
            rv = execve(cmd_path, args_list, shell->env);
            fprintf(stderr, "error of %d\n", errno);
            if (rv)
                ft_lst_add_status_back(&shell->all_status, ft_lstnew_status(errno), shell);
        }
        free(cmd_path);
    }
    else
    {
        ft_lst_add_status_back(&shell->all_status, ft_lstnew_status(127), shell);
        fprintf(stderr, "bash: %s: command not found\n", args_list[0]);
    }
    if (g_stop_signal != 2)
        g_stop_signal = -1;
}