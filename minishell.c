#include "execution.h"
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>


char *find_command_path(char *s)
{
    char **env_list;
    int i;

    i = 0;
    env_list = ft_split(getenv("PATH"), ':');
    char	*command;
	char	*tmp;

	if (access(s, F_OK | X_OK) == 0)
	{
		command = ft_strdup1(s);
		return (command);
	}
	
	while (*env_list)
	{
		tmp = ft_strjoin(*env_list, "/");
		if (!tmp)
			return (NULL);
		command = ft_strjoin(tmp, s);
		free(tmp);
		if (!command)
			return (NULL);
		if (access(command, F_OK | X_OK) == 0)
			return (command);
		free(command);
		env_list++;
	}
	return (NULL);
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    char *command;
    char **args_list;
    char cwd[150];
    char *cmd_path;
    pid_t child;
    while (1)
    {
        getcwd(cwd, 150);
        printf("%s", cwd);
        command = readline(">> ");
        if (command)
        {
            args_list = ft_split(command, ' ');
            if (!ft_strncmp(args_list[0], "cd", 3))
            {
                if (args_list[1])
                    chdir(args_list[1]);
                else
                    chdir(getenv("HOME"));
            }
            else
            {
                cmd_path = find_command_path(args_list[0]);
                if (cmd_path)
                {
                    child = fork();
                    if (child == 0)
                        execve(cmd_path, args_list, envp);
                    waitpid(-1, NULL, 0);
                }
                else
                    printf("command not found: %s\n", args_list[0]);
            }
        }
        else
            printf("\n");
        free(command);
    }
}