#include "execution.h"

void change_directory(char *path)
{
    if (path)
        chdir(path);
    else
        chdir(getenv("HOME"));
}

int env_exists(char *name, char **env)
{
    char **split;

    while (*env)
    {
        split = ft_split(*env, '=');
        if (!ft_strncmp(split[0], name, ft_strlen(name) + 1))
            return (1);
        free(split);
        env++;
    }
    return (0);
}

void update_env(char *env_name, char *data, char ***env)
{
    char **new_environ;

    new_environ = malloc(sizeof(char *) * (list_len(*env) + 1));
    if (new_environ)
    {
        copy_list_updating(env_name, data, new_environ, env);
        *env = new_environ;
    }
}

void add_env(char *data, char ***env)
{
    char **new_environ;

    new_environ = malloc(sizeof(char *) * (list_len(*env) + 2));
    if (new_environ)
    {
        ft_memcpy(new_environ, *env, list_len(*env) * sizeof(char *));
        new_environ[list_len(new_environ)] = data;
        new_environ[list_len(new_environ) + 1] = NULL;
        *env = new_environ;
    }
}
void add_update_env(char *data, char ***env)
{
    char **split_env = ft_split(data, '=');
    if (env_exists(split_env[0], *env))
        update_env(split_env[0], data, env);
    else
        add_env(data, env);
}

void remove_env(char *data, char ***env)
{
    char **new_environ = malloc(sizeof(char *) * (list_len(*env)));
    if (new_environ)
    {
        copy_list_excluding(new_environ, data);
        *env = new_environ;                    
    }
}

void exit_shell(char *status)
{
    int value;

    value = ft_atoi(status);
    //!!TODO: check if status is not bigger than INT_MAX
    if (status)
        exit(value);
}

void execute_binary(char **args_list, char ***env)
{
    char *cmd_path;
    pid_t child;
    
    cmd_path = find_command_path(args_list[0]);
    if (cmd_path)
    {
        child = fork();
        if (child == 0)
            execve(cmd_path, args_list, *env);
        waitpid(-1, NULL, 0);
    }
    else
        printf("command not found: %s\n", args_list[0]);
}