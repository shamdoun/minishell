#include "minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*copy;
	int		len;

	len = ft_strlen(s1);
	copy = malloc(len + 1);
	if (copy)
	{
		ft_memmove(copy, s1, len);
		copy[len] = '\0';
	}
	return (copy);
}
