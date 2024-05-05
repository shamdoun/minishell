#include "../minishell.h"

void handle_signal(int sig)
{
    if (sig == 2)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    else if (sig == 3)
        return ;
}