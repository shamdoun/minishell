#include "../minishell.h"

t_commands	*create_commands(t_commands *list, char *content)
{
	t_commands	*new;
	t_commands	*head;

	head = list;
	new = malloc(sizeof(t_commands));
	if (new == NULL)
		return (free_list(list), NULL);
	new->command = content;
	new->next = NULL;
	if (list == NULL)
	{
		list = new;
		return (list);
	}
	while (list->next)
		list = list->next;
	list->next = new;
	return (head);
}

int	cmd_lenght(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '|')
		i++;
	return (i);
}

// split the command ( | ) 
t_commands	*create_cmd(char *input)
{
	int			i;
	int			j;
	char		*cmd;
	t_commands	*cmd_list;

	cmd_list = NULL;
	while (*input)
	{
		j = 0;
		i = cmd_lenght(input);
		cmd = malloc((sizeof(char) * i) + 1);
		if (cmd == NULL)
			return (NULL);
		while (*input && *input != '|')
		{
			cmd[j] = *input;
			(1) && (j++, input++);
		}
		(1) && (cmd[j] = '\0', cmd_list = create_commands(cmd_list, cmd));
		if (cmd_list == NULL)
			return (NULL);
		if (*input)
			input++;
	}
	return (cmd_list);
}
