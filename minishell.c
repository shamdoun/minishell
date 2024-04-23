#include "minishell.h"

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    t_shell *minishell = malloc(sizeof(t_shell));
    // minishell->all_allocated_data = NULL;
    minishell->all_input = NULL;
    // minishell->all_status = NULL;
    minishell->env = env;
    t_input *new_input = ft_lstnew_input();
    new_input->command_name = "cat";
    new_input->args = NULL;
    ft_lst_add_input_back(&minishell->all_input, new_input);
    t_file *file1 = ft_lstnew_file("Makefile", 3, NULL);
    ft_lst_add_file_back(&minishell->all_input->all_files, file1);
    execute_input(minishell);
    free(minishell);
}
