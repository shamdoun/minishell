#include "execution.h"

static void run_built_ins(t_command *command, t_status **s_list, char ***env)
{
    char **args_list;
    (void)s_list;
    args_list = ft_split(command->input, ' ');
    if (!ft_strncmp(args_list[0], "cd", 3))
        change_directory(args_list[1], s_list, env);
    else if (!ft_strncmp(args_list[0], "export", 7))
        add_update_env(args_list[1], s_list, env);
    else if(!ft_strncmp(args_list[0], "unset", 6))
        remove_env(args_list[1], s_list, env);
    else if (!ft_strncmp(args_list[0], "exit", 5))
        exit_shell(command,  args_list[1], *s_list);
    else if (!ft_strncmp(args_list[0], "echo", 5))
        echo_message(&args_list[1]);
    else if (!ft_strncmp(args_list[0], "env", 4))
        print_all_env_vars(*env);
    else
        execute_binary(args_list, s_list, env);
    free_array(args_list);
}

void echo_message(char **args)
{
    //!!TODO:parse args
    if (args[1])
        printf("%s", args[1]);
    else
        printf("%s\n", args[0]);
}

void execute_input(t_command *command, char ***env, t_status **s_list)
{
    command->type = 1;
    if (command->type == 1)
        run_built_ins(command, s_list, env);
    // else if (mode == 2)
    //     redirection(command);
    // else
    //     piping(command);
}