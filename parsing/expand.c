#include "../minishell.h"

static int	ft_strlenex(char *cmd)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (cmd[i] && cmd[i] != '$')
	{
		if (cmd[i] == '\'')
		{
			(1) && (len++, i++);
			while (cmd[i] != '\'')
				(1) && (i++, len++);
		}
		len++;
		i++;
	}
	return (len);
}

static char	*ft_put_str(char *cmd, int len)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(len + 1);
	while (cmd[i] && cmd[i] != '$')
	{
		if (cmd[i] == '\'')
		{
			str[i] = cmd[i];
			i++;
			while (cmd[i] && cmd[i] != '\'')
				(1) && (str[i] = cmd[i], i++);
		}
		str[i] = cmd[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int	ft_strlenquotes(char *str)
{
	char	*del;
	int		len;
	int		i;

	del = " \t'\".#!%%&()*+,-/:;<=>?@[]\\^{}|~$";
	i = 1;
	len = 0;
	while (str[i] && !ft_strchr(del, str[i]))
	{
		len++;
		i++;
	}
	return (len);
}

static char	*ft_getname(char *str, t_shell *shell, int len)
{
	char	*ptr;
	char	*s;
	int		i;

	ptr = malloc(len + 1);
	i = 1;
	while (len)
	{
		ptr[i - 1] = str[i];
		i++;
		--len;
	}
	ptr[i - 1] = '\0';
	s = ft_getenv(ptr, shell->env);
	if (!s)
		s = shell->r_path;
	if (s == NULL)
		return (NULL);
	i = 0;
	while (s && s[i])
		i++;
	free(ptr);
	ptr = malloc(i + 1);
	i = 0;
	while (s && s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_expand(char *cmd, t_shell *shell)
{
	char	*ptr;
	char	*str;
	int		len;
	int		i;

	i = 0;
	str = NULL;
	len = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$')
		{
			len = ft_strlenquotes(cmd + i);
			ptr = ft_getname(cmd + i, shell, len);
			i += len + 1;
			str = ft_azejoin(&str, ptr);
			free(ptr);
		}
		if (cmd[i])
		{
			len = ft_strlenex(cmd + i);
			ptr = ft_put_str(cmd + i, len);
			str = ft_azejoin(&str, ptr);
			free(ptr);
			i += len - 1;
			len = 0;
			i++;
		}
	}
	//printf("%s\n", str);
	return (str);
}

// int	main(int ac, char **av, char **env)
// {
// 	char *test = "hello \"$USER\" klds";
// 	char *ptr;

// 	ptr = ft_expand(test, env);
// 	printf("%s\n", ptr);
// 	return (0);
// }
