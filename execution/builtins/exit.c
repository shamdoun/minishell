#include "../execution.h"

int ft_last_status(t_status *list)
{
    if (!list)
        return (0);
    while (list->next)
        list = list->next;
    return (list->status);
}


void exit_shell(t_shell *shell, t_arg *status)
{
    int value;

    while (shell->all_allocated_data)
    {
        free(shell->all_allocated_data);
        shell->all_allocated_data = shell->all_allocated_data->next;
    }    
    if (status)
    {
        value = ft_atoi(status->arg);
        exit(value);
    }
    else
        exit(ft_last_status(shell->all_status));
}