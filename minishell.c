#include "execution.h"

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    char *command;
    char cwd[150];
    while (1)
    {
        getcwd(cwd, 150);
        printf("%s", cwd);
        command = readline(">> ");
        if (command)
        {
            execute_input(command, &env, 1);
            add_history(command);
        }
        else
            printf("\n");
        free(command);
    }
}