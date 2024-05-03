#include "../execution.h"

int ft_last_status(t_status *list)
{
    while (list->next)
        list = list->next;
    return (list->status);
}


void exit_shell(t_shell *shell, t_arg *status)
{
    int value;
    //!!TODO: check if status is not bigger than INT_MAX
    // free(command->input);
    while (shell->all_allocated_data)
    {
        free(shell->all_allocated_data);
        shell->all_allocated_data = shell->all_allocated_data->next;
    }    if (status)
    {
        value = ft_atoi(status->arg);
        exit(value);
    }
    else
        exit(ft_last_status(shell->all_status));
}