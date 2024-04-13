#include "execution.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
    char *command;
    while (1)
    {
        command = readline("-> minishell ");
        if (command)
            ft_putstr_fd(command, 1);
        ft_putchar_fd('\n', 1);
        free(command);
    }
}