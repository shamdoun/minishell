#include "execution.h"

void run_built_ins(char *command, char ***env)
{
    char **args_list;

    args_list = ft_split(command, ' ');
    if (!ft_strncmp(args_list[0], "cd", 3))
        change_directory(args_list[1]);
    else if (!ft_strncmp(args_list[0], "export", 7))
        add_update_env(args_list[1], env);
    else if(!ft_strncmp(args_list[0], "unset", 6))
        remove_env(args_list[1], env);
    else if (!ft_strncmp(args_list[0], "exit", 5))
        exit_shell(args_list[1]);
    else
        execute_binary(args_list, env);
}


void execute_input(char *command, char ***env, int mode)
{
    if (mode == 1)
        run_built_ins(command, env);
    // else if (mode == 2)
    //     redirection(command);
    // else
    //     piping(command);
}