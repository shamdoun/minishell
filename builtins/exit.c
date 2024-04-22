#include "../execution.h"

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