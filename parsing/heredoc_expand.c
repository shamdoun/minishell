#include "../minishell.h"

static int	ft_strlennl(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '\n')
		i++;
	return (i);
}

static char	*ft_strnnl(char *cmd)
{
	char	*s;
	int		i;

	i = ft_strlennl(cmd);
	s = malloc(i + 1);
	i = 0;
	while (cmd[i] && cmd[i] != '\n')
	{
		s[i] = cmd[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_strwnl(char *s)
{
	char	*str;
	int		i;

	i = ft_strlennl(s);
	str = ft_malloc(i + 2, 0);
	i = 0;
	while (s && s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\n';
	str[i + 1] = '\0';
	return (str);
}

char	*ft_expand_hd(char *cmd, t_shell *shell)
{
	t_expVar	v;

	(1) && (v.i = 0, v.v = 1, v.str = NULL, v.len = 0, v.s = ft_strnnl(cmd));
	while (v.s[v.i])
	{
		if (v.s[v.i] == '$')
		{
			v.len = ft_strlenquotes(v.s + v.i);
			v.ptr = ft_getname(v.s + v.i, shell, v.len);
			(1) && (v.i += v.len + 1, v.str = ft_azejoin(&v.str, v.ptr));
			free(v.ptr);
		}
		if (v.s[v.i])
		{
			v.len = ft_strlenex(v.s + v.i, v.v);
			v.ptr = ft_put_str(v.s + v.i, v.len, v.v);
			v.str = ft_azejoin(&v.str, v.ptr);
			free(v.ptr);
			(1) && (v.i += v.len - 1, v.len = 0, v.i++);
		}
	}
	v.str = ft_strwnl(v.str);
	return (v.str);
}
