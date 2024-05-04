#include "../execution.h"

char *ft_getenv(char *name, char **env)
{
    char **split;
    char *found;

    while (*env)
    {
        split = ft_split_1(*env, '=');
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

int ft_same_path(char *p1, char *p2)
{
    char *cp1;
    char *cp2;

    cp1 = ft_strdup(p1);
    cp2 = ft_strdup(p2);
    ft_str_tolower(cp1);
    ft_str_tolower(cp2);
    if (!ft_strncmp(cp1, cp2, ft_strlen(cp2)))
    {
        free(cp1);
        free(cp2);
        return (1);
    }
    free(cp1);
    free(cp2);
    return (0);
}

void update_cwd(char *cwd, t_arg *path)
{
    char **split_cwd;
    char **split_path;
    int i, j;
    char *joined;

    if (!path || !ft_strncmp(path->arg, "~", 2) || !ft_strncmp(path->arg, "..", 3))
        return ;
    if (ft_same_path(path->arg, cwd))
    {
        strcpy(cwd, path->arg);
        return ;
    }
    split_cwd = ft_split_1(cwd, '/');
    split_path = ft_split_1(path->arg, '/');
    i = 0, j = 0;
    joined = ft_strdup("/");
    while (!ft_strncmp(split_path[j], ".", 2) || !ft_strncmp(split_path[j], "..", 2))
    {
        free(split_path[j]);
        split_path++;
    }
    while (i < list_len(split_cwd) - list_len(split_path))
    {
        joined = ft_strjoin(joined, split_cwd[i]);
        joined = ft_strjoin(joined, "/");
        i++;
    }
    while (split_cwd[i])
    {
        strcpy(split_cwd[i], split_path[j]);
        joined = ft_strjoin(joined, split_cwd[i]);
        j++;
        if (split_path[j])
            joined = ft_strjoin(joined, "/");
        i++;
    }
    strcpy(cwd, joined);
    free(joined);
}

void change_directory(t_arg *path, t_shell *shell, char ***env)
{
    int return_value;
    char *home;

    return_value = 0;
    if (path && ft_strncmp(path->arg, "~", 2))
        return_value = chdir(path->arg);
    else
    {
        home = ft_getenv("HOME", *env);
        if (home)
            return_value = chdir(home);
        ft_lst_add_ad_back(&shell->all_allocated_data, ft_lstnew_ad(home));
    }
    if (return_value)
    {
        ft_lst_add_status_back(&shell->all_status, ft_lstnew_status(errno));
        perror("cd");
    }
    getcwd(shell->cwd, sizeof(shell->cwd));
    update_cwd(shell->cwd, path);
}

