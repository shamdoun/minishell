#include "../minishell.h"


//creating new input node and checking command_name's value
// int main()
// {
//     t_shell *minishell = malloc(sizeof(t_shell));
//     minishell->all_input = NULL;
//     t_input *input = ft_lstnew_input();
//     input->command_name = "first command";
//     ft_lst_add_input_back(&minishell->all_input, input);
//     printf("%s\n", minishell->all_input->command_name);
//     free(minishell);
// }

// //creating new status node and checking its value
// int main()
// {
//     t_shell *minishell = malloc(sizeof(t_shell));
//     minishell->all_input = NULL;
//     minishell->all_status = NULL;
//     t_status *input = ft_lstnew_status(0);
//     ft_lst_add_status_back(&minishell->all_status, input);
//     printf("%d\n", minishell->all_status->status);
//     free(minishell);
// }


// //creating new file node and checking its value
// int main()
// {
//     t_shell *minishell = malloc(sizeof(t_shell));
//     minishell->all_input = NULL;
//     t_input *input = ft_lstnew_input();
//     ft_lst_add_input_back(&minishell->all_input, input);
//     t_file *f = ft_lstnew_file("new file", 0, NULL);
//     ft_lst_add_file_back(&minishell->all_input->all_files, f);
//     printf("%s\n", minishell->all_input->all_files->file_name);
//     free(minishell);
// }

//creating new allocated_data node and checking its value
// int main()
// {
//     t_shell *minishell = malloc(sizeof(t_shell));
//     printf("%p\n", minishell);
//     minishell->all_allocated_data = NULL;
//     t_a_data *ad = ft_lstnew_ad(minishell);
//     ft_lst_add_ad_back(&minishell->all_allocated_data, ad);
//     printf("%p\n", minishell->all_allocated_data->address);
//     free(minishell);
// }
