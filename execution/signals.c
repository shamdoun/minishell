#include "../minishell.h"

extern volatile sig_atomic_t stop_signal;

void handle_signal(int sig)
{
    static int nl;

    if (stop_signal == 1 || stop_signal == 2 || stop_signal == -1)
        nl = 0;
    else if (stop_signal == 3)
        nl = 1;
    if (sig == 2)
    {
        if (!nl)
            write(1, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}