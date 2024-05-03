#include "../minishell.h"

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

	// atexit(f);
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, &handle_signal);
	(void)argc;
	(void)argv;
	minishell = malloc(sizeof(t_shell));
	minishell->all_allocated_data = NULL;
	minishell->all_status = NULL;
	ft_lst_add_status_back(&minishell->all_status, ft_lstnew_status(0));
	minishell->all_input = NULL;
	minishell->env = env;
	if (isatty(STDIN_FILENO))
	{
		while (1)
		{
			getcwd(minishell->cwd, sizeof(minishell->cwd));
			printf("%s", minishell->cwd);
			input = readline("$> ");
			if (!input)
				exit_shell(minishell, NULL);
			if (*input != '\0')
			{
				add_history(input);
				check = ft_parsing(input);
				if (check)
				{
					cmds = create_cmd(input);
					if (cmds == NULL)
						(perror("allocation failed..."), exit (1));
					add_space(cmds);
					minishell->all_input = split_cmd(cmds);
					if (!minishell->all_input)
						printf("syntax error\n");
					execute_input(minishell);
				}
				else
					printf("syntax error\n");
			}
		}
	}
	else
		printf("failed\n");
	return (0);
}
