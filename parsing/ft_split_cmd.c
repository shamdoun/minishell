#include "../minishell.h"

static void	put_redirection(t_input *nw, char *str, char *name)
{
	t_file	*new;
	char	*ptr;	

	new = NULL;
	ptr = remove_quotes(name);
	if (!strncmp(str, "<", 2))
		new = ft_lstnew_file(ptr, 3, NULL);
	else if (!strncmp(str, ">", 2))
		new = ft_lstnew_file(ptr, 1, NULL);
	else if (!strncmp(str, ">>", 3))
		new = ft_lstnew_file(ptr, 2, NULL);
	else if (!strncmp(str, "<<", 3))
		new = ft_lstnew_file(NULL, 4, ptr);
	ft_lst_add_file_back(&(nw->all_files), new);
}

static t_arg	*put_arg(t_arg *arguments, char *str)
{
	t_arg	*new;
	t_arg	*head;
	char	*ptr;

	ptr = remove_quotes(str);
	head = arguments;
	new = malloc(sizeof(t_arg));
	if (!new)
		return (NULL);
	new->arg = ptr;
	new->next = NULL;
	if (!arguments)
	{
		arguments = new;
		return (arguments);
	}
	while (head->next)
		head = head->next;
	head->next = new;
	return (arguments);
}

static int	check_last(char *str)
{
	if (!strncmp(str, ">", 2))
		return (0);
	else if (!strncmp(str, "<", 2))
		return (0);
	else if (!strncmp(str, ">>", 3))
		return (0);
	else if (!strncmp(str, "<<", 3))
		return (0);
	return (1);
}

static int	filltoken(t_commands *cmd, t_input *new)
{
	char	**str;
	int		i;
	int		t;

	str = ft_split(cmd->command);
	(1) && (i = 0, t = 0);
	while (str[i])
		i++;
	if (i - 1 >= 0 && !check_last(str[i - 1]))
		return (ft_free_split(str), 0);
	i = 0;
	while (str[i])
	{
		if (str[i][0] == '<' || str[i][0] == '>')
		{
			put_redirection(new, str[i], str[i + 1]);
			i++;
		}
		else if (t == 0)
			(1) && (t = 1, new->command_name = str[i]);
		else
			(new)->args = put_arg((new)->args, str[i]);
		i++;
	}
	return (1);
}

t_input	*split_cmd(t_commands *cmd)
{
	t_commands	*head;
	t_input		*tokenize;
	t_input		*new;
	int			check;

	tokenize = NULL;
	head = cmd;
	while (cmd)
	{
		new = ft_lstnew_input();
		check = filltoken(cmd, new);
		if (!check)
			return (free_tokenize(tokenize), free_list(head), NULL);
		ft_lst_add_input_back(&tokenize, new);
		cmd = cmd->next;
	}
	//free_list(head);
	return (tokenize);
}
