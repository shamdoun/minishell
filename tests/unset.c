#include "../minishell.h"

//unsetting a default variable
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
    new_input->command_name = "unset";
    new_input->args = "TERM";
    getcwd(new_input->cwd, PATH_MAX);
    ft_lst_add_input_back(&minishell->all_input, new_input);
    execute_input(minishell);
    print_all_env_vars(minishell->env);
    free(minishell);
}


//creating a new variable then unsetting it
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
    new_input->command_name = "export";
    new_input->args = "test=works";
    getcwd(new_input->cwd, PATH_MAX);
    ft_lst_add_input_back(&minishell->all_input, new_input);
    execute_input(minishell);
    print_all_env_vars(minishell->env);
    printf("------------------------------------------------------------------------------------------------------------\n");
    new_input->command_name = "unset";
    new_input->args = "test";
    execute_input(minishell);
    print_all_env_vars(minishell->env);
    free(minishell);
}

