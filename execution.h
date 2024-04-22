#include "minishell.h"


void remove_env(char *data, t_shell *shell, char ***env);
void add_update_env(char *data, t_shell *shell, char ***env);
void exit_shell(t_shell *shell, char *status);
void execute_binary(char **args_list, t_shell *shell, char ***env);
void execute_input(t_shell *shell, char ***env);
void print_all_env_vars(char **env);
void echo_message(char **args);
void change_directory(char *path, t_shell *shell, char ***env);
char *ft_getenv(char *name, char **env);
char *find_command_path(char *s);
void copy_list_updating(char *env_name, t_status **s_list, char *data, char **new_environ, char ***old_env);
int list_len(char **list);