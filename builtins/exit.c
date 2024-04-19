#include "../execution.h"

void exit_shell(t_command *command, char *status, t_status *s_list)
{
    int value;
    (void)s_list;
    (void)command;
    //!!TODO: check if status is not bigger than INT_MAX
    // free(command->input);
    if (status)
    {
        value = ft_atoi(status);
        exit(value);
    }
    else
        exit(ft_lstlast(s_list)->status);
}