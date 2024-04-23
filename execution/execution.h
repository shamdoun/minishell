#include "../minishell.h"


void remove_env(char *data, t_shell *shell, char ***env);
void add_update_env(char *data, t_shell *shell, char ***env);
void exit_shell(t_shell *shell, char *status);
void execute_binary(t_shell *shell);
void print_all_env_vars(char **env);
void echo_message(char *args);
void change_directory(char *path, t_shell *shell, char ***env);
char *ft_getenv(char *name, char **env);
char *find_command_path(char *s);
void copy_list_updating(char *env_name, char *data, t_shell *shell, char **new_environ);
int list_len(char **list);
int ft_last_status(t_status *list);
void redirect_streams(t_shell *shell);