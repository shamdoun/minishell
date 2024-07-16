/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:10:36 by shamdoun          #+#    #+#             */
/*   Updated: 2024/07/16 12:25:49 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// extern volatile sig_atomic_t	g_signal;

void leaks()
{
    fclose(gfp);
    system("leaks minishell");
    usleep(1000 * 100 *10000);
}

static int	check_cmds(t_commands *cmd)
{
	t_commands	*head;
	char		**str;
	int			i;

	head = cmd;
	while (head)
	{
		i = 0;
		str = ft_split(head->command);
		while (str[i])
		{
			if ((!ft_strncmp(str[i], "<<", ft_strlen(str[i]))
				|| !ft_strncmp(str[i], ">>", ft_strlen(str[i])))
				&& str[i + 1] && (!ft_strncmp(str[i + 1], "<<", ft_strlen(str[i + 1]))
				|| !ft_strncmp(str[i + 1], ">>", ft_strlen(str[i + 1]))))
				return (1);
			i++;
		}
		head = head->next;
	}
	ft_free_split(str);
	return (0);
}

static void	check_execute(char *input, t_shell *minishell)
{
	int			check;
	t_commands	*cmds;
	
	check = ft_parsing(input);
	if (check)
	{
		cmds = create_cmd(input);
		// printf("node 1: commandName: %s; Node_pointer: %p CommandPointer: %p\n", cmds->command, cmds, cmds->command);
		// printf("node 2: commandName: %s; Node_pointer: %p CommandPointer: %p\n", cmds->next->command, cmds->next, cmds->next->command);
		// printf("node 3: commandName: %s; Node_pointer: %p CommandPointer: %p\n", cmds->next->next->command, cmds->next->next, cmds->next->next->command);
		if (cmds == NULL)
			(perror("allocation failed..."), exit (1));
		add_space(cmds);
		check = check_cmds(cmds);
		if (check)
			(add_new_status(minishell, 258), perror("syntax error\n"));
		else
		{
			minishell->all_input = split_cmd(cmds, minishell);
			if (!minishell->all_input)
			{
				
				(perror("minishell->all_input failed\n"),
					add_new_status(minishell, 258));
				return ;
			}
			(ft_recover_echo(),
				execute_input(minishell), ft_hide_ctrl_c());
		}
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
	gfp = fopen("test/leaks", "w");
	if (!gfp)
		perror("");
	// atexit(leaks);
	minishell = NULL;
	init(&minishell, env);
	handle_all_signals(0);
	ft_reset_terminal(0);
	if (1)
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
