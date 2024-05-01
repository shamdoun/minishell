#include "minishell.h"

void	free_tokenize(t_input *token)
{
	while (token)
	{
		while (token->args)
		{
			free(token->args);
			token->args = token->args->next;
		}
		while (token->all_files)
		{
			free(token->all_files);
			token->all_files = token->all_files->next;
		}
		free(token->command_name);
		free(token);
	}
}
