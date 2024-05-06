#include "../minishell.h"

volatile sig_atomic_t stop_signal = 0;

void f()
{
	system("leaks minishell");
}

void init(t_shell **minishell, char **env)
{
	//initializing minishell structure
	(*minishell) = malloc(sizeof(t_shell));
	if (!(*minishell))
		exit(1);
	(*minishell)->all_allocated_data = NULL;
	(*minishell)->all_status = NULL;
	(*minishell)->all_input = NULL;
	(*minishell)->env = env;
	(*minishell)->r_path = NULL;
	getcwd((*minishell)->cwd, sizeof((*minishell)->cwd));
	//checking if env is empty
	if (!(*env))
		add_default_env(*minishell);
	else
		update_inhereted_env(*minishell, env);
	if (!ft_getenv("_", env) || ft_strncmp(ft_getenv("_", env), "/usr/bin/env", 13))
		update_env_path_var(*minishell);
}

void ft_hide_ctrl_c(void)
{
	struct termios ter;

	tcgetattr(STDIN_FILENO, &ter);

	ter.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &ter);
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
    int     	check;
	t_commands	*cmds;
	t_shell		*minishell;

	// signals
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, SIG_IGN);
	(void)argc;
	(void)argv;
	minishell = NULL;
	init(&minishell, env);
	ft_hide_ctrl_c();
	if (isatty(1))
	{
		while (1)
		{
			signal(SIGINT, &handle_signal);
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
					minishell->all_input = split_cmd(cmds);
					if (!minishell->all_input)
						printf("syntax error\n");
					execute_input(minishell);
				}
				else
					printf("syntax error\n");
				add_history(input);
			}
		}
	}
	else
		printf("failed\n");
	return (0);
}
