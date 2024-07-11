/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:10:36 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/11 21:50:38 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// extern volatile sig_atomic_t	g_signal;

// void leaks()
// {
//     // fclose(gfp);
//     system("leaks minishell");
//     usleep(1000 * 100 *10000);
// }

static void	check_execute(char *input, t_shell *minishell)
{
	int			check;
	t_commands	*cmds;

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
		(ft_recover_echo(),
			execute_input(minishell), ft_hide_ctrl_c());
	}
	else
	{
		add_new_status(minishell, 258);
		perror("syntax error\n");
	}
	add_history(input);
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_shell		*minishell;

	(void)argc;
	(void)argv;
	minishell = NULL;
	init(&minishell, env);
	handle_all_signals(0);
	ft_reset_terminal(0);
	if (isatty(STDIN_FILENO))
	{
		while (1)
		{
			input = readline("minishell$> ");
			if (!input)
				exit_shell(minishell, NULL, 1);
			if (*input != '\0')
				check_execute(input, minishell);
			free(input);
			ft_reset_terminal(1);
		}
	}
	else
		printf("failed\n");
	return (1);
}
