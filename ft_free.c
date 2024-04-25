#include "minishell.h"

void    ft_free(char **ptr, int last)
{
    while (--last >= 0)
    {
        free(*ptr);
    }
    free(ptr);
}

void	free_fail(t_parse_list **list)
{
	while((*list))
	{
		free(*list);
		(*list) = (*list)->next;
	}
}

void	free_list(t_commands *list)
{
	while (list)
	{
		free(list->command);
		free(list);
		list = list->next;
	}
}
