#include "minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*copy;
	int		len;

	len = ft_strlen(s1);
	copy = ft_malloc(len + 1, 0);
	if (copy)
	{
		ft_memmove(copy, s1, len);
		copy[len] = '\0';
	}
	return (copy);
}

char	*ft_strdup_v3(const char *s1, int mode)
{
	char	*copy;
	int		len;

	len = ft_strlen(s1);
	copy = ft_malloc(len + 1, mode);
	if (copy)
	{
		ft_memmove(copy, s1, len);
		copy[len] = '\0';
	}
	return (copy);
}
