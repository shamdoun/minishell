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
    t_input *input1 = ft_lstnew_input();
    input1->command_name = "cd";
    input1->args = "..";
    ft_lst_add_input_back(&minishell->all_input, input1);
    t_input *input2 = ft_lstnew_input();
    input2->command_name = "echo";
    input2->args = "hello world";
    ft_lst_add_input_back(&minishell->all_input, input2);
    execute_input(minishell);
    free(minishell);
}
