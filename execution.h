#ifndef EXECUTION_H
# define EXECUTION_H
#include "./libft/libft.h"
#include "./pipex/bonus/pipex_bonus.h"
#include "./pipex/gnl/get_next_line.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>

//status linked list to store all return values
typedef struct status_list
{
    int status;
    struct status_list *next;
    struct allocated_data *all_a_data;    
} t_status;

typedef struct allocated_data{
    void *data;
    struct allocated_data *next;
} t_a_data;

typedef struct command_data
{
    char *input;
    struct allocated_data *a_data_list;
    int     type;
} t_command;

void execute_input(t_command *command, char ***env, t_status **s_list);
char *find_command_path(char *s);
void copy_list_excluding(char **new_environ, char **old_env, char *str);
int list_len(char **list);
void change_directory(char *path, t_status **s_list, char ***env);
void add_update_env(char *data, t_status **s_list, char ***env);
void remove_env(char *data, t_status **s_list, char ***env);
void exit_shell(t_command *command, char *status, t_status *s_list);
void execute_binary(char **args_list, t_status **s_list, char ***env);
void copy_list_updating(char *env_name, t_status **s_list, char *data, char **new_environ, char ***old_env);
void	ft_lstadd_back(t_status **lst, t_status *new);
void ft_lstadd_allocated_data_back(t_a_data **lst, t_a_data *new);
t_a_data	*ft_lstnew_a_data(void *content);
void echo_message(char **args);
void print_all_env_vars(char **env);
t_status	*ft_lstnew(int content);
t_status	*ft_lstlast(t_status *lst);
#endif