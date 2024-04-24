#include "minishell.h"

void	ft_free(char **ptr, int last)
{
	while (--last >= 0)
		free(ptr[last]);
	free(ptr);
}
