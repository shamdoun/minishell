#include "../minishell.h"

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
    new_input->command_name = "cd";
    getcwd(new_input->cwd, PATH_MAX);
    new_input->args = "~";
    ft_lst_add_input_back(&minishell->all_input, new_input);
    printf("%s>>\n", minishell->all_input->cwd);
    execute_input(minishell);
    getcwd(new_input->cwd, PATH_MAX);
    printf("%s>>\n", minishell->all_input->cwd);
    free(minishell);
}