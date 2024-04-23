#include "minishell.h"

static char	*ft_skipchar(char *str)
{
	char	q;

	while (*str && *str != ' ' && *str != '\t')
	{
		if (*str == '"' || *str == '\'')
		{
			q = *str;
			str++;
			while (*str != q)
				str++;
			str++;
		}
		str++;
	}
	return (str);
}

static int	ft_count_words(char *str)
{
	int		count;
	char	q;

	count = 0;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
		{
			count++;
			q = *(str++);
			while (*str != q)
				str++;
			str++;
		}
		else if (*str == ' ' || *str == '\t')
			str++;
		else
		{
			count++;
			str = ft_skipchar(str);
		}
	}
	return (count);
}

static int	ft_strlenght(char *str)
{
	int		len;
	char	q;

	len = 0;
	while (*str && *str != ' ' && *str != '\t')
	{
		if (*str == '"' || *str == '\'')
		{
			q = *str;
			while (*str && *str != q)
				(1) && (str++, len++);
		}
		(1) && (str++, len++);
	}
	return (len);
}

static char	*ft_fillstr(char *str)
{
	char	q;
	char	*val;
	int		i;
	int		len;

	(1) && (i = 0, len = ft_strlenght(str));
	val = malloc(len + 1);
	if (!val)
		return (NULL);
	while (*str && *str != ' ' && *str != '\t')
	{
		if (*str == '"' || *str == '\'')
		{
			q = *str;
			val[i++] = *str;
			while (*(++str) != q)
				val[i++] = *str;
			val[i++] = *(str++);
		}
		else
			val[i] = *str;
		(1) && (i++, str++);
	}
	val[i] = '\0';
	return (val);
}

char	**ft_split(char *str)
{
	char	**ptr;
	char	q;
	int		j;

	(1) && (j = ft_count_words(str), ptr = malloc(sizeof(char *) * (j + 1)));
	if (!ptr)
		return (NULL);
	(1) && (ptr[j] = NULL, j = 0);
	while (*str)
	{
		ptr[j++] = ft_fillstr(str);
		while (*str && *str != ' ' && *str != '\t')
		{
			if (*str == '\'' || *str == '"')
			{
				q = *(str++);
				while (*str && *str != q)
					str++;
			}
			str++;
		}
		if (*str)
			str++;
	}
	return (ptr);
}
