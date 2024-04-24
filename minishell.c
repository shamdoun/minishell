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
    new_input->command_name = "echo";
    new_input->args = "fda fdsamds";
    ft_lst_add_input_back(&minishell->all_input, new_input);
    t_file *file1 = ft_lstnew_file("f1", 1, "da");
    t_file *file2 = ft_lstnew_file("f2", 2, "da");
    t_file *file3 = ft_lstnew_file("Makefile", 3, "da");
    t_file *file4 = ft_lstnew_file(NULL, 4, "da");
    t_file *file5 = ft_lstnew_file("f1", 1, "da");
    ft_lst_add_file_back(&minishell->all_input->all_files, file1);
    ft_lst_add_file_back(&minishell->all_input->all_files, file2);
    ft_lst_add_file_back(&minishell->all_input->all_files, file3);
    ft_lst_add_file_back(&minishell->all_input->all_files, file4);
    ft_lst_add_file_back(&minishell->all_input->all_files, file5);
    execute_input(minishell);
    free(minishell);
}
