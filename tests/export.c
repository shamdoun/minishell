#include "../minishell.h"
//creating a new environment
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
    new_input->args = "test=rea";
    getcwd(new_input->cwd, PATH_MAX);
    ft_lst_add_input_back(&minishell->all_input, new_input);
    execute_input(minishell);
    print_all_env_vars(minishell->env);
    free(minishell);
}

//creating a new environment and updating its value
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
    new_input->args = "test=before";
    getcwd(new_input->cwd, PATH_MAX);
    ft_lst_add_input_back(&minishell->all_input, new_input);
    execute_input(minishell);
    new_input->args = "test=after";
    execute_input(minishell);
    print_all_env_vars(minishell->env);
    free(minishell);
}

//updating a default environment variable
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
    new_input->args = "TERM=new_term";
    getcwd(new_input->cwd, PATH_MAX);
    ft_lst_add_input_back(&minishell->all_input, new_input);
    execute_input(minishell);
    print_all_env_vars(minishell->env);
    free(minishell);
}


