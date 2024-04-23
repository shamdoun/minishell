#include "../execution.h"

int ft_last_status(t_status *list)
{
    while (list->next)
        list = list->next;
    return (list->status);
}


void exit_shell(t_shell *shell, char *status)
{
    int value;
    //!!TODO: check if status is not bigger than INT_MAX
    // free(command->input);
    if (status)
    {
        value = ft_atoi(status);
        exit(value);
    }
    else
        exit(ft_last_status(shell->all_status));
}