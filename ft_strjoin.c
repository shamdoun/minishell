#include "minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, ft_strlen(s1) + 1);
	ft_strlcat(result, s2, ft_strlen(s2) + ft_strlen(s1) + 1);
	return (result);
}
