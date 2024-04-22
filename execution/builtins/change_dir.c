#include "../execution.h"

char *ft_getenv(char *name, char **env)
{
    char **split;
    char *found;

    while (*env)
    {
        split = ft_split(*env, '=');
        if (!ft_strncmp(split[0], name, ft_strlen(name) + 1))
        {
            found = ft_strdup(split[1]);
            free_array(split);
            return (found);
        }
        free_array(split);
        env++;
    }
    return (NULL);
}

void change_directory(char *path, t_shell *shell, char ***env)
{
    int return_value;

    return_value = 0;
    if (path && ft_strncmp(path, "~", 2))
        return_value = chdir(path);
    else
    {
        path = ft_getenv("HOME", *env);
        if (path)
            return_value = chdir(path);
        ft_lst_add_ad_back(&shell->all_allocated_data, ft_lstnew_ad(path));
    }
    if (return_value)
    {
        ft_lst_add_ad_back(&shell->all_status, ft_lstnew_status(errno));
        perror("cd");
    }
}

