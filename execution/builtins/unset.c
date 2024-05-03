#include "../execution.h"

void copy_list_excluding(char **new_environ, char **old_env, char *str)
{
    char **p;
    int i = 0;
    while (i < list_len(old_env))
    {
        p = ft_split_1(old_env[i], '=');
        if (ft_strncmp(str, p[0], ft_strlen(str)))
        {
            ft_memcpy(new_environ, &old_env[i], sizeof(char *));
            new_environ++;
        }
        free_array(p);
        i++;
    }
    *new_environ = NULL;
}


void remove_env(t_arg *data, t_shell *shell, char ***env)
{
    char **new_environ = malloc(sizeof(char *) * (list_len(*env)));
    if (new_environ)
    {
        copy_list_excluding(new_environ, *env, data->arg);
        ft_lst_add_ad_back(&shell->all_allocated_data, ft_lstnew_ad(new_environ));
        *env = new_environ;             
    }
    else
        ft_lst_add_status_back(&shell->all_status, ft_lstnew_status(errno)); 
}