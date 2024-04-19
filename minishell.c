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
    status_list->all_a_data = NULL;
    ft_lstadd_allocated_data_back(&status_list->all_a_data, ft_lstnew_a_data(command));
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
            free(command->input);
            t_a_data *tmp;
            while(status_list->all_a_data)
            {
                tmp = status_list->all_a_data;
                free(status_list->all_a_data->data);
                status_list->all_a_data = status_list->all_a_data->next;
                free(tmp);
            }
            ft_lstadd_back(&status_list, ft_lstnew(0));
            return (ft_lstlast(status_list)->status);
        }
        free(command->input);
    }
    //!!TODO: free all status_list
    free(command);
    return (0);
}