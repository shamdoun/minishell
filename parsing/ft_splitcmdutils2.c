#include "../minishell.h"

char	*get_cmdname(char *s, char **env)
{
	char	*ptr;
	char	*str;
	int		t;

	t = ft_isexpanded(s);
	ptr = NULL;
	str = NULL;
	if (t)
	{
		ptr = ft_expand(s, env);
		str = remove_quotes(ptr);
		free(ptr);
	}
	else
		str = remove_quotes(s);
	return (str);
}