#include "../../minishell.h"


void	add_new_status(t_shell *shell, int status)
{
	t_status	*s;

	s = malloc(sizeof(t_status));
	if (!s)
		exit(1);
	s->status = status;
	s->next = NULL;
	ft_lst_add_status_back(&shell->all_status, s,  shell);
}