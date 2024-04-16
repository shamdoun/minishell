#ifndef EXECUTION_H
# define EXECUTION_H
#include "./libft/libft.h"
#include "./pipex/bonus/pipex_bonus.h"
#include "./pipex/gnl/get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

//status linked list to store all return values
typedef struct status_list
{
    int status;
    struct status_list *next;
} status_t;

void execute_input(char *command, char ***env, int mode);
char *find_command_path(char *s);
void copy_list_excluding(char **new_environ, char *str);
int list_len(char **list);
void change_directory(char *path);
void add_update_env(char *data, char ***env);
void remove_env(char *data, char ***env);
void exit_shell(char *status);
void execute_binary(char **args_list, char ***env);
void add_update_env(char *data, char ***env);
void copy_list_updating(char *env_name, char *data, char **new_environ, char ***old_env);
#endif