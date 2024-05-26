#include "../../minishell.h"

extern volatile sig_atomic_t	g_signal;

void	add_new_status(t_shell *shell, int status)
{
	t_status	*s;
	(void)shell;
	
	s = ft_malloc(sizeof(t_status), 0);
	if (!s)
		return ;
	s->status = status;
	s->next = NULL;
	ft_lst_add_status_back(&shell->all_status, s,  shell);
	if (g_signal == 2)
		g_signal = 0;
}

int	ft_array_size(char **list)
{
	int	n;

	n = 0;
	if (!list)
		return (n);
	while (list[n])
		n++;
	return (n);
}

int	ft_is_executable(char *cmd_path)
{
	char **split_cmd_path;

	split_cmd_path = ft_split_1(cmd_path, '/');
	if (!split_cmd_path)
		return (2);
	if (!split_cmd_path[1] && !ft_strncmp(split_cmd_path[1], "minishell", ft_strlen(split_cmd_path[1])))
		return (1);
	else if (!ft_strncmp(split_cmd_path[ft_array_size(split_cmd_path) - 1], "minishell", ft_strlen(split_cmd_path[ft_array_size(split_cmd_path) - 1])))
		return (1);
	return (0);
}