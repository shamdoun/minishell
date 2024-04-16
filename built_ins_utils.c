#include "execution.h"

extern char** environ;
char *find_command_path(char *s)
{
    char **env_list;
    int i;

    i = 0;
    env_list = ft_split(getenv("PATH"), ':');
    char	*command;
	char	*tmp;

	if (access(s, F_OK | X_OK) == 0)
	{
		command = ft_strdup1(s);
		return (command);
	}
	
	while (*env_list)
	{
		tmp = ft_strjoin(*env_list, "/");
		if (!tmp)
			return (NULL);
		command = ft_strjoin(tmp, s);
		free(tmp);
		if (!command)
			return (NULL);
		if (access(command, F_OK | X_OK) == 0)
			return (command);
		free(command);
		env_list++;
	}
	return (NULL);
}

void copy_list_updating(char *env_name, char *data, char **new_environ, char ***old_env)
{
    char **old_list;
    char **p;

    int i = 0;
    old_list = *old_env;
    while (i < list_len(old_list))
    {
            p = ft_split(old_list[i], '=');
            if (ft_strncmp(env_name, p[0], ft_strlen(env_name) + 1))
                ft_memcpy(new_environ, &old_list[i], sizeof(char *));
            else
                ft_memcpy(new_environ, &data, sizeof(char *));
            new_environ++;
            free(p);
            i++;
    }
    *new_environ = NULL;
}

void copy_list_excluding(char **new_environ, char *str)
{
    char **p;
    int i = 0;
    while (i < list_len(environ))
    {
        p = ft_split(environ[i], '=');
        if (ft_strncmp(str, p[0], ft_strlen(str) + 1))
        {
            ft_memcpy(new_environ, &environ[i], sizeof(char *));
            new_environ++;
        }
        free(p);
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