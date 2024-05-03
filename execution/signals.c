#include "../minishell.h"

void handle_signal(int sig)
{
    if (sig == 1)
    {
        printf("Quit: \n");
        exit(131);
    }
    else if (sig == 2)
        write(1, "interupting\n", 13);
    else if (sig == 3)
        return ;
}