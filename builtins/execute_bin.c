#include "../execution.h"

void execute_binary(char **args_list, t_shell *shell, char ***env)
{
    char *cmd_path;
    pid_t child;
    
    cmd_path = find_command_path(args_list[0]);
    if (cmd_path)
    {
        child = fork();
        if (child == 0)
        {
            int rv;
            rv = execve(cmd_path, args_list, *env);
            fprintf(stderr, "error of %d\n", errno);
            if (rv)
                ft_lst_add_status_back(&shell->all_status, ft_lstnew_status(errno));
        }
        waitpid(-1, NULL, 0);
        free(cmd_path);
    }
    else
    {
        ft_lst_add_status_back(shell->all_status, ft_lstnew(127));
        printf("command not found: %s\n", args_list[0]);
    }
}