#include "../execution.h"

int ft_last_status(t_status *list)
{
    t_status *head;

    head = list;
    if (!head)
        return (0);
    while (head->next)
        head = head->next;
    return (head->status);
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