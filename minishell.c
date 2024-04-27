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
    input1->command_name = "echo";
    input1->args = NULL;
    // t_file *f1 = ft_lstnew_file("f1", 2, "end");

    t_file *f2 = ft_lstnew_file("f1", 3, "end");
    // t_file *f3 = ft_lstnew_file(NULL, 4, "Makefile");
    // ft_lst_add_file_back(&input1->all_files, f1);
    ft_lst_add_file_back(&input1->all_files, f2);
    // ft_lst_add_file_back(&input1->all_files, f3);
    // ft_lst_add_file_back(&input1->all_files, f3);
    ft_lst_add_input_back(&minishell->all_input, input1);
    
    t_input *input2 = ft_lstnew_input();
    input2->command_name = "cat";
    input2->args = NULL;
    t_file *f4 = ft_lstnew_file("f2", 4, "gsafds");
    ft_lst_add_file_back(&input2->all_files, f4);
    ft_lst_add_input_back(&minishell->all_input, input2);
    execute_input(minishell);
    free(minishell);
}
