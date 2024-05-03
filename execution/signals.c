#include "../minishell.h"

void handle_signal(int sig)
{
    if (sig == 2)
        write(1, "\nminishell$> ", 14);
    else if (sig == 3)
        return ;
}