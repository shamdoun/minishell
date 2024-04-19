#include "../execution.h"

int env_exists(char *name, char **env)
{
    char **split;
    while (*env)
    {
        split = ft_split(*env, '=');
        if (!ft_strncmp(split[0], name, ft_strlen(name) + 1))
        {
            free_array(split);
            return (1);
        }
        free_array(split);
        env++;
    }
    return (0);
}

void update_env(char *env_name, t_status **s_list, char *data, char ***env)
{
    char **new_environ;
    new_environ = malloc(sizeof(char *) * (list_len(*env) + 1));
    if (new_environ)
    {
        copy_list_updating(env_name, s_list, data, new_environ, env);
        ft_lstadd_allocated_data_back(&(*s_list)->all_a_data, ft_lstnew_a_data(new_environ));
        *env = new_environ;
    }
    else
        ft_lstadd_back(s_list, ft_lstnew(errno));
}

void add_env(char *data, t_status **s_list, char ***env)
{
    char **new_environ;
    char *new_data;

    new_environ = malloc(sizeof(char *) * (list_len(*env) + 2));
    if (new_environ)
    {
        ft_memcpy(new_environ, *env, list_len(*env) * sizeof(char *));
        new_data = ft_strdup(data);
        new_environ[list_len(*env)] = new_data;
        new_environ[list_len(*env) + 1] = NULL;
        *env = new_environ;
        ft_lstadd_allocated_data_back(&(*s_list)->all_a_data, ft_lstnew_a_data(new_data));
        ft_lstadd_allocated_data_back(&(*s_list)->all_a_data, ft_lstnew_a_data(new_environ));
    }
    else
        ft_lstadd_back(s_list, ft_lstnew(errno));
}

void add_update_env(char *data, t_status **s_list, char ***env)
{
    char **split_env = ft_split(data, '=');
    if (env_exists(split_env[0], *env))
        update_env(split_env[0], s_list, data, env);
    else
        add_env(data, s_list, env);
    free_array(split_env);
}
