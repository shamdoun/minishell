#include "../minishell.h"

int	ft_strlenex(char *cmd, int v)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (cmd[i] && cmd[i] != '$')
	{
		if (v == 0)
		{
			if (cmd[i] == '\'')
			{
				(1) && (len++, i++);
				while (cmd[i] != '\'')
					(1) && (i++, len++);
			}
			(1) && (len++, i++);
		}
		else
			(1) && (len++, i++);
	}
	return (len);
}

char	*ft_put_str(char *cmd, int len, int v)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(len + 1);
	while (cmd[i] && cmd[i] != '$')
	{
		if (v == 0)
		{
			if (cmd[i] == '\'')
			{
				str[i] = cmd[i];
				i++;
				while (cmd[i] && cmd[i] != '\'')
					(1) && (str[i] = cmd[i], i++);
			}
			(1) && (str[i] = cmd[i], i++);
		}
		if (v == 1)
			(1) && (str[i] = cmd[i], i++);
	}
	str[i] = '\0';
	return (str);
}

int	ft_strlenquotes(char *str)
{
	char	*del;
	int		len;
	int		i;

	del = " \t'\".#!%%&()*+,-/:;<=>@[]\\^{}|~$";
	i = 1;
	len = 0;
	while (str[i] && !ft_strchr(del, str[i]))
	{
		len++;
		i++;
	}
	return (len);
}

char	*ft_getname(char *str, t_shell *shell, int len)
{
	char	*ptr;
	char	*s;
	int		i;

	i = 1;
	if (str[i] == '?')
		return (ptr = ft_itoa(ft_last_status(shell->all_status)));
	ptr = malloc(len + 1);
	while (len)
		(1) && (ptr[i - 1] = str[i], i++, --len);
	ptr[i - 1] = '\0';
	s = ft_getenv(ptr, shell->env);
	if (!s)
		s = shell->r_path;
	if (s == NULL)
		return (NULL);
	i = 0;
	while (s && s[i])
		i++;
	(1) && (free(ptr), ptr = malloc(i + 1), i = 0);
	while (s && s[i])
		(1) && (ptr[i] = s[i], i++);
	return (ptr[i] = '\0', ptr);
}

char	*ft_expand(char *cmd, t_shell *shell)
{
	char	*ptr;
	char	*str;
	int		len;
	int		i;
	int		v;

	i = 0;
	v = 0;
	str = NULL;
	len = 0;
	// if (cmd[ft_strlen(cmd) - 1] == '\n')
	// 	cmd[ft_strlen(cmd) - 1] = '\0';
	while (cmd[i])
	{
		if (v == 0 && cmd[i] == '"')
			v = 1;
		else if (cmd[i] == '"')
			v = 0;
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
			len = ft_strlenex(cmd + i, v);
			ptr = ft_put_str(cmd + i, len, v);
			str = ft_azejoin(&str, ptr);
			free(ptr);
			i += len - 1;
			len = 0;
			i++;
		}
	}
	// printf("expanded string %s\n", str);
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
