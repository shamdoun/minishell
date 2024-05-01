#include "../minishell.h"

static int	check_syntax(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i > 0 && (str[i - 1] == ' ' || str[i - 1] == '\t'))
		i--;
	if (str[i - 1] == '\\' || str[i - 1] == '<' || str[i - 1] == '>')
		return (1);
	return (0);
}

static t_parse_list	*ft_lstnew(char content)
{
	t_parse_list	*new_node;

	new_node = malloc(sizeof(t_parse_list));
	if (new_node == NULL)
		return (NULL);
	new_node->ch = content;
	new_node->next = NULL;
	return (new_node);
}

static void	ft_lstadd_back(t_parse_list **lst, t_parse_list *new)
{
	t_parse_list	*t;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	t = *lst;
	while (t->next)
		t = t->next;
	t->next = new;
}

static void	create_new_node(t_parse_list **list, char c, int where)
{
	t_parse_list	*new;

	new = ft_lstnew(c);
	if (new == NULL)
		(free_fail(list), perror("malloc failed"), exit (1));
	if (where == 0)
		new->type = 's';
	else
		new->type = 'c';
	ft_lstadd_back(list, new);
}

// the idea is puting every charachter inside a node in a linked list
int	ft_parsing(char *str)
{
	int				i;
	char			*special_char;
	t_parse_list	*input_list;

	(1) && (special_char = "~`#$&*()\\[]|{};'\"<>/?!",
	input_list = NULL, i = -1);
	while (str[++i])
	{
		if (ft_strchr(special_char, str[i]))
			create_new_node(&input_list, str[i], 0);
		else
			create_new_node(&input_list, str[i], 1);
	}
	i = ft_checkquotes(input_list);
	if (i == 1 || check_syntax(str) || check_operator(str))
	{
		free_fail(&input_list);
		return (0);
	}
	return (ft_free_inputlist(&input_list), 1);
}
