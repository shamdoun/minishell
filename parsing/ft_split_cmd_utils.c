#include "../minishell.h"

int	ft_isexpanded(char *str)
{
	char	*del;
	int		i;

	(1) && (i = 0, del = " \t'\".#!%%&()*+,-/:;<=>@[]\\^{}|~$");
	if (!ft_strncmp(str, "$", 2))
		return (0);
	while (str[i])
	{
		if (str[i] == '"')
		{
			while (str[++i] && str[i] != '"')
				if (str[i] == '$' && str[i + 1] && !ft_strchr(del, str[i + 1]))
					return (1);
		}
		if (str[i] == '\'')
			while (str[++i] && str[i] != '\'')
				;
		if (str[i] == '$' && !ft_strchr(del, str[i + 1]))
			return (1);
		if (str[i] == '$' && ft_strchr("\"'", str[i + 1]))
			return (1);
		if (str[i])
			i++;
	}
	return (0);
}

int	ft_lenwithoutquotes(char *str)
{
	char	q;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			q = str[i];
			i++;
			while (str[i] != q)
				(1) && (i++, len++);
			i++;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*remove_quotes(char *str)
{
	char	*ptr;
	char	q;
	int		i;
	int		j;

	if (!str)
		return (0);
	i = ft_lenwithoutquotes(str);
	ptr = malloc(i + 1);
	(1) && (i = 0, j = 0);
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			(1) && (q = str[i], i++);
			while (str[i] != q)
				(1) && (ptr[j] = str[i], j++, i++);
			i++;
		}
		else
			(1) && (ptr[j] = str[i], i++, j++);
	}
	return (ptr[j] = '\0', ptr);
}

void	put_delimiter(t_input *nw, char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	nw->all_files->delimeter = malloc(i + 1);
	i = 0;
	while (str[i])
	{
		nw->all_files->delimeter[i] = str[i];
		i++;
	}
	nw->all_files->delimeter[i] = '\0';
}

void	put_filename(t_input *nw, char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	nw->all_files->file_name = malloc(i + 1);
	i = 0;
	while (str[i])
	{
		nw->all_files->file_name[i] = str[i];
		i++;
	}
	nw->all_files->file_name[i] = '\0';
}

void	put_cmdname(t_input *nw, char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	nw->command_name = malloc(i + 1);
	i = 0;
	while (str[i])
	{
		nw->command_name[i] = str[i];
		i++;
	}
	nw->command_name[i] = '\0';
}
