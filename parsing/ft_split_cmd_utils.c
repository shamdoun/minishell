#include "../minishell.h"

void	put_delimiter(t_input *nw, char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	nw->all_files->delimeter = malloc(i + 1);
	i = 0;
	while (str[i])
	{
		nw->all_files->delimeter[i] = str[i];
		i++;
	}
	nw->all_files->delimeter[i] = '\0';
}

void	put_filename(t_input *nw, char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	nw->all_files->file_name = malloc(i + 1);
	i = 0;
	while (str[i])
	{
		nw->all_files->file_name[i] = str[i];
		i++;
	}
	nw->all_files->file_name[i] = '\0';
}

void	put_cmdname(t_input *nw, char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	nw->command_name = malloc(i + 1);
	i = 0;
	while (str[i])
	{
		nw->command_name[i] = str[i];
		i++;
	}
	nw->command_name[i] = '\0';
}
