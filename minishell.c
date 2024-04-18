#include "execution.h"


void f()
{
    system("leaks minishell");
}

int main(int argc, char **argv, char **env)
{
    static t_status *status_list;

    (void)argc;
    (void)argv;
    (void)env;
    char cwd[150];
    t_command *command = malloc(sizeof(t_command));
    ft_lstadd_back(&status_list, ft_lstnew(0));
    atexit(f);
    while (1)
    {
        getcwd(cwd, 150);
        printf("%s", cwd);
        command->input = readline(">> ");
        if (command->input && ft_strlen(command->input))
            execute_input(command, &env, &status_list);
        else
        {
            ft_lstadd_back(&status_list, ft_lstnew(0));
            return (ft_lstlast(status_list)->status);
        }
        free(command->input);
    }
    //!!TODO: free all status_list
    free(command);
    return (0);
}