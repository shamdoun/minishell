#include "../execution.h"


char *find_command_path(char *s)
{
    char **env_list;
    int i;
    char	*command;
	char	*tmp;

	if (access(s, F_OK | X_OK) == 0)
	{
		command = ft_strdup1(s);
		return (command);
	}

    env_list = ft_split(getenv("PATH"), ':');
	i = 0;
    while (env_list[i])
	{
		tmp = ft_strjoin(env_list[i], "/");
		if (!tmp)
			return (NULL);
		command = ft_strjoin(tmp, s);
		free(tmp);
		if (!command)
        {
            free_array(env_list);
			return (NULL);
        }
        if (access(command, F_OK | X_OK) == 0)
        {
            free_array(env_list);
			return (command);
        }
        free(command);
		i++;
	}
    free_array(env_list);
	return (NULL);
}

void copy_list_updating(char *env_name, char *data, t_shell *shell, char **new_environ)
{
    char **old_list;
    char **p;

    int i = 0;
    old_list = shell->env;
    while (i < list_len(old_list))
    {
            p = ft_split(old_list[i], '=');
            if (ft_strncmp(env_name, p[0], ft_strlen(env_name)))
                ft_memcpy(new_environ, &old_list[i], sizeof(char *));
            else
            {
                data = ft_strdup(data);
                ft_lst_add_ad_back(&shell->all_allocated_data, ft_lstnew_ad(data));
                ft_memcpy(new_environ, &data, sizeof(char *));
            }
            new_environ++;
            free_array(p);
            i++;
    }
    *new_environ = NULL;
}

int list_len(char **list)
{
    int i;

    i = 0;
    while (list[i])
        i++;
    return (i);
}