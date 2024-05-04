#include "../execution.h"

void print_all_env_vars(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
}

void declare_all_envs(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        printf("declare -x %s\n", env[i]);
        i++;
    }
}