#include "../minishell.h"

static void	put_redirection(t_input *nw, char *str, char *name, t_shell *shell)
{
	t_file	*new;
	int		t_f;
	char	*ptr;
	char	*s;

	(1) && (new = NULL, ptr = NULL, s = NULL, t_f = 0);
	if (!strncmp(str, "<", 2) || !strncmp(str, ">", 2) || !strncmp(str, ">>", 3))
	{
		t_f = ft_isexpanded(name);
		if (t_f)
			ptr = ft_expand(name, shell);
		else
			ptr = name;
		s = remove_quotes(ptr);
		if (!strncmp(str, "<", 2))
			new = ft_lstnew_file(s, 3, NULL);
		else if (!strncmp(str, ">", 2))
			new = ft_lstnew_file(s, 1, NULL);
		else if (!strncmp(str, ">>", 3))
			new = ft_lstnew_file(s, 2, NULL);
	}
	else if (!strncmp(str, "<<", 3))
	{
		ptr = remove_quotes(name);
		new = ft_lstnew_file(NULL, 4, ptr);
	}
	if (!new)
		return ;
	ft_lst_add_file_back(&(nw->all_files), new, shell);
}

static t_arg	*put_arg(t_arg *arguments, char *str, t_shell *shell)
{
	t_arg	*new;
	t_arg	*head;
	char	*ptr;

	head = arguments;
	ptr = NULL;
	new = ft_malloc(sizeof(t_arg), 0);
	if (!new)
		return (NULL);
	new->t_f = ft_isexpanded(str);
	if (new->t_f)
		ptr = ft_expand(str, shell);
	else
		ptr = str;
	new->arg = remove_quotes(ptr);
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

static int	filltoken(t_commands *cmd, t_input *new, t_shell *shell)
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
			put_redirection(new, str[i], str[i + 1], shell);
			i++;
		}
		else if (t == 0)
			(1) && (t = 1, new->command_name = get_cmdname(str[i], shell));
		else
		{
			(new)->args = put_arg((new)->args, str[i], shell);
			//printf("%p\n", new->args);
		}
		i++;
	}
	free_array(str);
	return (1);
}

t_input	*split_cmd(t_commands *cmd, t_shell *shell)
{
	t_commands	*head;
	t_input		*tokenize;
	t_input		*new;
	int			check;

	tokenize = NULL;
	head = cmd;
	shell->is_expanded = 0;
	while (cmd)
	{
		new = ft_lstnew_input();
		if (!new)
			return NULL;
		check = filltoken(cmd, new, shell);

		if (!check)
			return (free_tokenize(tokenize), free_list(head), NULL);
		ft_lst_add_input_back(&tokenize, new, shell);
		cmd = cmd->next;
	}
	free_list(head);
	return (tokenize);
}
