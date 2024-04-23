#include "../minishell.h"

//executing a bin with args
int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    t_shell *minishell = malloc(sizeof(t_shell));
    minishell->all_allocated_data = NULL;
    minishell->all_input = NULL;
    minishell->all_status = NULL;
    minishell->env = env;
    t_input *new_input = ft_lstnew_input();
    new_input->command_name = "cat";
    new_input->args = "../MAKEFILE";
    ft_lst_add_input_back(&minishell->all_input, new_input);
    execute_input(minishell);
    free(minishell);
}

//executing a bin without args
int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    t_shell *minishell = malloc(sizeof(t_shell));
    minishell->all_allocated_data = NULL;
    minishell->all_input = NULL;
    minishell->all_status = NULL;
    minishell->env = env;
    t_input *new_input = ft_lstnew_input();
    new_input->command_name = "ls";
    new_input->args = NULL;
    ft_lst_add_input_back(&minishell->all_input, new_input);
    execute_input(minishell);
    free(minishell);
}

