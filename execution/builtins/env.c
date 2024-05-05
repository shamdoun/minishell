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

void 		update_env_path_var(t_shell *shell)
{
    t_arg *new_envpath;

    new_envpath = malloc(sizeof(t_arg));
    if (!new_envpath)
        perror("failed!");
    new_envpath->arg = ft_strdup("_=/usr/bin/env");
    add_update_env(new_envpath, shell, &shell->env);
    free(new_envpath->arg);
    free(new_envpath);
}

void update_shlvl(t_shell *shell)
{
    int new_value;
    char *var;
    // char *new_shlvl;
    char *tmp;
    t_arg *new_shlvl;

    var = ft_getenv("SHLVL", shell->env);
    if (!var)
        perror("failed!");
    //check if env is reseted
    new_value = ft_atoi(var) + 1;
    if  (new_value == 1000)
    {
        perror("bash: warning: shell level (1000) too high, resetting to 1");
        tmp = ft_itoa(1);
    }
    else
        tmp = ft_itoa(new_value);
    if (!tmp)
        perror("failed!");
    new_shlvl = malloc(sizeof(t_arg));
	new_shlvl->arg = ft_strjoin("SHLVL=", tmp);
    if (!new_shlvl->arg)
        perror("failed!");
    add_update_env(new_shlvl, shell, &shell->env);
    free(new_shlvl);
    free(tmp);
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