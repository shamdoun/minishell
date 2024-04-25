#include "minishell.h"

int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (*(s + i))
	{
		if (*(s + i) == (char)c)
			return (1);
		i++;
	}
	return (0);
}
