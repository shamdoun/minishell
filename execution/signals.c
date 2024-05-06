#include "../minishell.h"

extern volatile sig_atomic_t stop_signal;

void handle_signal(int sig)
{
    if (sig == 2)
    {
        if (!stop_signal)
            write(1, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}