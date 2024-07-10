#include "../minishell.h"

char	*get_cmdname(char *s, t_shell *shell)
{
	char	*ptr;
	char	*str;
	int		t;

	t = ft_isexpanded(s);
	ptr = NULL;
	str = NULL;
	if (t)
	{
		ptr = ft_expand(s, shell);
		str = remove_quotes(ptr);
		shell->is_expanded = 1;
	}
	else
		str = remove_quotes(s);
	return (str);
}
