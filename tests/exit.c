#include "../minishell.h"

//exit without indicating a status
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
    new_input->command_name = "exit";
    new_input->args = NULL;
    ft_lst_add_input_back(&minishell->all_input, new_input);
    t_status *status = ft_lstnew_status(0);
    ft_lst_add_status_back(&minishell->all_status, status);
    execute_input(minishell);
    free(minishell);
}

//exit with a status
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
    new_input->command_name = "exit";
    new_input->args = "5";
    ft_lst_add_input_back(&minishell->all_input, new_input);
    t_status *status = ft_lstnew_status(0);
    ft_lst_add_status_back(&minishell->all_status, status);
    execute_input(minishell);
    free(minishell);
}

