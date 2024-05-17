#include "../minishell.h"

extern volatile sig_atomic_t	g_signal;

void f()
{
	system("leaks minishell");
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
	// signals
	handle_all_signals(0);
	// signal(SIGINT, &handle_ctrl_c);
	// signal(SIGQUIT, SIG_IGN);
	minishell = NULL;
	//init
	last_exit = 0;
	if (1)
	{
		while (1)
		{
			init(&minishell, env, last_exit);
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
				if (g_signal == 2)
				{
					add_new_status(minishell, 1);
					g_signal = 0;
				}
			}
			if (g_signal == 2)
			{
				add_new_status(minishell, 1);
				g_signal = -3;
			}
			else if (g_signal == -3)
			{
				add_new_status(minishell, 0);
				g_signal = 0;
			}
			last_exit = ft_last_status(minishell->all_status);
		}
	}
	else
		printf("failed\n");
	return (0);
}
