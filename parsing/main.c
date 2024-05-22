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
	int			last_exit;

	(void)argc;
	(void)argv;
	// gfp = fopen("test/leaks", "w");
	// signals
	// atexit(leaks);
	handle_all_signals(0);
	minishell = NULL;
	//init
	last_exit = 0;
	int is_new_shell;
	char *inherited_r_path;
	char *cwd;

	inherited_r_path = NULL;
	is_new_shell = 1;
	cwd = NULL;
	if (1)
	{
		while (1)
		{
			if (init_shell_struct(&minishell, env, last_exit, cwd))
				ft_putendl_fd(FAILED_MALLOC, 2);
			else
			{
				init_shell_environment(&minishell, &is_new_shell, inherited_r_path);
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
				last_exit = ft_last_status(minishell->all_status);
				env = minishell->env;
				inherited_r_path = minishell->r_path;
				cwd = minishell->cwd;
			}
		}
	}
	else
		printf("failed\n");
	return (0);
}
