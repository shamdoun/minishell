#include "../minishell.h"


void add_update_env(t_arg *data, t_shell *shell, char ***env);
void execute_binary(t_shell *shell, int mode);
void print_all_env_vars(char **env);
void echo_message(t_arg *args);
void change_directory(t_arg *path, t_shell *shell, char ***env);
char *find_command_path(char *s);
void copy_list_updating(char *env_name, char *data, t_shell *shell, char **new_environ);
int list_len(char **list);
int ft_last_status(t_status *list);
void redirect_streams(t_shell *shell);
void pipex(t_shell *shell, int mode);
void run_built_ins(t_shell *shell, int mode);
void open_input_files(t_shell *shell);
char *ft_join_args(t_arg *args);
void declare_all_envs(char **env);