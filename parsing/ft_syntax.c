#include "../minishell.h"

int	ft_checkquotes(t_parse_list *list)
{
	int		i;
	char	c;

	i = 0;
	while (list)
	{
		if (list->ch == '"' || list->ch == '\'')
		{
			(1) && (i = 1, c = list->ch);
			list = list->next;
			while (i != 0 && list)
			{
				if (c == list->ch)
				{
					i = 0;
					break ;
				}
				list = list->next;
			}
		}
		if (list)
			list = list->next;
	}
	return (i);
}

int	check_operator(char *s)
{
	int		k;
	char	o;

	while (*s)
	{
		k = 0;
		if (*s == '\'' || *s == '"')
		{
			o = *s;
			s++;
			while (*s && *s != o)
				s++;
		}
		if (*s == '<' || *s == '>')
		{
			o = *s;
			while (*s && *s == o)
				(1) && (s++, k++);
			if (k > 2)
				return (1);
		}
		s++;
	}
	return (0);
}
