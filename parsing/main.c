#include "../minishell.h"

int	main()
{
	char		buf[1024];
	char		*input;
    int     	check;
	t_commands	*cmds;

	if (isatty(STDIN_FILENO))
	{
		getcwd(buf, sizeof(buf));
		while (1)
		{
			input = readline("$> ");
			if (input == 0)
                break;
			add_history(input);
            check = ft_parsing(input);
			if (check)
			{
				cmds = create_cmd(input);
				if (cmds == NULL)
					(perror("allocation failed..."), exit (1));
				// while (cmds)
				// {
				// 	printf("%s\n", cmds->command);
				// 	cmds = cmds->next;
				// }
				add_space(cmds);
				while (cmds)
				{
					printf("%s\n", cmds->command);
					cmds = cmds->next;
				}
			}
			else
				printf("syntax error\n");
		}
	}
	else
		printf("failed\n");
	return (0);
}