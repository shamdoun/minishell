#include "../execution.h"

int env_exists(char *name, char **env)
{
    char **split;
    while (*env)
    {
        split = ft_split(*env, '=');
        if (!ft_strncmp(split[0], name, ft_strlen(name)))
        {
            free_array(split);
            return (1);
        }
        free_array(split);
        env++;
    }
    return (0);
}

void update_env(char *env_name, t_shell *shell, char *data, char ***env)
{
    char **new_environ;
    new_environ = malloc(sizeof(char *) * (list_len(*env) + 1));
    if (new_environ)
    {
        copy_list_updating(env_name, data, shell, new_environ);
        ft_lst_add_ad_back(&shell->all_allocated_data, ft_lstnew_ad(new_environ));
        *env = new_environ;
    }
    else
        ft_lst_add_status_back(&shell->all_status, ft_lstnew_status(errno));
}

void add_env(char *data, t_shell *shell, char ***env)
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
        ft_lst_add_ad_back(&shell->all_allocated_data, ft_lstnew_ad(new_data));
        ft_lst_add_ad_back(&shell->all_allocated_data, ft_lstnew_ad(new_environ));
    }
    else
        ft_lst_add_status_back(&shell->all_status, ft_lstnew_status(errno));
}

void add_update_env(char *data, t_shell *shell, char ***env)
{
    char **split_env = ft_split(data, '=');
    if (env_exists(split_env[0], *env))
        update_env(split_env[0], shell, data, env);
    else
        add_env(data, shell, env);
    free_array(split_env);
}
