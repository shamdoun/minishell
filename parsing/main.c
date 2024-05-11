#include "../minishell.h"

extern volatile sig_atomic_t	g_stop_signal;

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

	(void)argc;
	(void)argv;
	// signals
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, SIG_IGN);
	minishell = NULL;
	//init
	init(&minishell, env);
	if (1)
	{
		while (1)
		{
			g_stop_signal = 0;
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
					ft_recover_echo();
					execute_input(minishell);
					ft_hide_ctrl_c();
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
