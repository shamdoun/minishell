#include "../minishell.h"

extern volatile sig_atomic_t	g_signal;


void	free_all(t_shell *minishell)
{
	t_a_data *tmp;

	while (minishell->all_allocated_data)
	{
		tmp = minishell->all_allocated_data;
		minishell->all_allocated_data = minishell->all_allocated_data->next;
		free(tmp->address);
		free(tmp);
		tmp = NULL;
	}
	free(minishell);
}


void copy_env_list(char ***new_env, char **old_env, size_t len)
{
	static t_a_data *nodes;
	t_a_data *head;
	t_a_data *tmp;
	size_t i = 0;

	while (i < len)
	{
		(*new_env)[i] = ft_strdup_v3(old_env[i], 2);
		tmp = ft_lstnew_ad(((*new_env)[i]));
		if (!i)
			head = tmp;
		ft_lst_add_ad_back(&nodes, tmp);
		i++;
	}
	(*new_env)[i] = NULL;

	//free
	while (nodes != head)
	{
		tmp = nodes;
		nodes = nodes->next;
		free(tmp->address);
		tmp->address = NULL;
		free(tmp);
		tmp = NULL;
	}
} 

void leaks()
{
    fclose(gfp);
    system("leaks minishell");
    usleep(1000 * 100 *10000);
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
    int     	check;
	t_commands	*cmds;
	t_shell		*minishell;

	(void)argc;
	(void)argv;
	// gfp = fopen("test/leaks", "w");
	// signals
	handle_all_signals(0);
	minishell = NULL;
	//init
	init(&minishell, env);
	if (1)
	{
		while (1)
		{
				input = readline("minishell$> ");
				if (!input)
					exit_shell(minishell, NULL);
				if (*input != '\0')
				{
					check = ft_parsing(input);
					if (check)
					{
						cmds = create_cmd(input);
						if (cmds == NULL)
							(perror("allocation failed..."), exit (1));
						add_space(cmds);
						minishell->all_input = split_cmd(cmds, minishell);
						if (!minishell->all_input)
							(perror("syntax error\n"), exit(1));
						(ft_recover_echo(), execute_input(minishell), ft_hide_ctrl_c());
					}
					else
						perror("syntax error\n");
					add_history(input);
				}
		}
	}
	else
		printf("failed\n");
	return (0);
}
