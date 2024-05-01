#include "../minishell.h"

int	main()
{
	char		buf[1024];
	char		*input;
    int     	check;
	t_commands	*cmds;
	t_input 	*minishell;

	if (isatty(STDIN_FILENO))
	{
		getcwd(buf, sizeof(buf));
		while (1)
		{
			input = readline("$> ");
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
					minishell = split_cmd(cmds);
					if (!minishell)
						printf("syntax error\n");
					while (minishell)
					{
						printf("command_name: %s\n", minishell->command_name);
						printf("ARGS: \n");
						while (minishell->args)
						{
							printf("\t%s\n", minishell->args->arg);
							minishell->args = minishell->args->next;
						}
						while (minishell->all_files)
						{
							printf("file_name->name: %s\n", minishell->all_files->file_name);
							printf("file_name->type: %d\n", minishell->all_files->type);
							printf("file_name->delimiter: %s\n", minishell->all_files->delimeter);
							minishell->all_files = minishell->all_files->next;
						}
						minishell = minishell->next;
					}
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
