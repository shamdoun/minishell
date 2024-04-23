#include  "../minishell.h"

//echo with flag in the middle
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
    new_input->command_name = "echo";
    new_input->args = "fsdgfd -n gfds";
    ft_lst_add_input_back(&minishell->all_input, new_input);
    execute_input(minishell);
    free(minishell);
}

//echo without flag
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
    new_input->command_name = "echo";
    new_input->args = "fsdgfd gfds";
    ft_lst_add_input_back(&minishell->all_input, new_input);
    execute_input(minishell);
    free(minishell);
}

//echo with one flag at the beginning of a string
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
    new_input->command_name = "echo";
    new_input->args = "fsdgfd -n gfds";
    ft_lst_add_input_back(&minishell->all_input, new_input);
    execute_input(minishell);
    free(minishell);
}

//echo with multiple flags at the beginning of a string
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
    new_input->command_name = "echo";
    new_input->args = "fsdgfd -n -n -n -n gfds";
    ft_lst_add_input_back(&minishell->all_input, new_input);
    execute_input(minishell);
    free(minishell);
}


