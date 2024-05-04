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

	// signals
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, &handle_signal);
	(void)argc;
	(void)argv;

	//initializing minishell structure
	minishell = malloc(sizeof(t_shell));
	minishell->all_allocated_data = NULL;
	minishell->all_status = NULL;
	minishell->all_input = NULL;
	minishell->env = env;
	//removing oldpwd from env list
	t_arg *oldpwd = malloc(sizeof(t_arg));
	oldpwd->arg = ft_strdup("OLDPWD");
	remove_env(oldpwd, minishell, &minishell->env);

	if (isatty(STDIN_FILENO))
	{
		getcwd(minishell->cwd, sizeof(minishell->cwd));
		while (1)
		{
			input = readline("minishell$> ");
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
