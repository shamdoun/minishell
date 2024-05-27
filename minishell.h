#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <libc.h>
#include <signal.h>
#include <stdbool.h>
#include <termios.h>
#include "./gnl/get_next_line.h"
#include "./execution/execution.h"


FILE*gfp;


// static void *_6malloc(size_t size, int line, const char *file)
// {
//     void *ptr = malloc(size);
//     fprintf(gfp, "['malloc', '%p, %i, '%s']\n", ptr, line, file);fflush(stdout);
//     return (ptr);

// }

// static void _6free(void*ptr , int line, const char *file)
// {
//     fprintf(gfp, "['free', '%p, %i, '%s']\n", ptr, line, file);fflush(stdout);
//     free(ptr);

// }


// #define malloc(x) _6malloc(x, __LINE__, __FILE__)
// #define free(x) _6free(x, __LINE__, __FILE__)
#define FAILED_MALLOC "failure"
#define WRONG_INPUT "No such file or directory"
#define POINT_INPUT "minishell: .: filename argument required \n.: usage: . filename [arguments]"
/*
	<<: 4
	>>: 2
	<: 3
	>: 1
*/

typedef struct	s_arg
{
	char			*arg;
	int				t_f;
	struct	s_arg	*next;
}	t_arg;

typedef struct file
{
	char	*file_name;
	int		type;
	char	*delimeter;
	struct file *next;
} t_file;

typedef struct input
{
	char			*command_name;
	t_arg			*args;
	struct file		*all_files;
	int				in_file;
	int				out_file;
	int				here_doc;
	int				t;
	struct input	*next;
} t_input;

typedef struct status {
	int				status;
	struct status	*next;
} t_status;

typedef struct allocated_data
{
	void					*address;
	struct allocated_data	*next;
} t_a_data;

typedef struct shell
{
	struct input			*all_input;
	struct status			*all_status;
	struct allocated_data	*all_allocated_data;
	char                    **env;
    char			        cwd[PATH_MAX];
	char 					*r_path;
	int						new_shell;
	int						env_updated;
} t_shell;

// to handle norminette errors on split
typedef struct  s_v
{
	char    **p;
	char    q;
	int     j;
}   t_v;

// handlig norminette on divide_cmd.c file
typedef struct	s_var
{
	int		j;
	char	q;
	char	*cmd;
}	t_var;

typedef struct  s_parse_list
{
	char					ch; // character
	char					type; // type of character (special or normal character)
	struct s_parse_list		*next;
}	t_parse_list;

/*
	the idea is to parse the commands if it has pipes
	example: echo "hello" > file.txt | echo "how are you" >> file.txt
	for the example, the linked list will had two nodes:
	first node: echo "hello" > file.txt
	second node: echo "how are you" >> file.txt
*/
typedef struct	s_commands
{
	char				*command;
	
	struct s_commands	*next;
}	t_commands;

typedef struct	s_space
{
	char	*p;
	char	o;
	int		l;
	int		i;
	int		j;
}	t_space;

typedef struct	pipex
{
	int	*ends;
	int	pipe_count;
	int	*processes;
} t_pipex;

void		ft_lst_add_input_back(t_input **lst, t_input *new, t_shell *shell);
void		ft_lst_add_ad_back(t_a_data **lst, t_a_data *new);
void		ft_lst_add_file_back(t_file **lst, t_file *new, t_shell *shell);
void		ft_lst_add_status_back(t_status **lst, t_status *new, t_shell *shell);
t_input		*ft_lstnew_input();
t_a_data	*ft_lstnew_ad(void *address);
t_status	*ft_lstnew_status(int status);
t_file	    *ft_lstnew_file(char *file_name, int type, char *delimeter);
size_t      ft_strlen(const char *);
int         ft_strncmp(const char *s1, const char *s2, size_t n);
void        execute_input(t_shell *shell);
void        free_array(char **a);
char	    *ft_strdup1(char *s);
// void        print_all_env_vars(char **env);
int	        ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	    ft_strlen(const char *s);
char		*ft_strjoin(char *s1, char *s2);
size_t	    ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	    ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_azejoin(char **s1, char *s2);
char	    *ft_strdup(const char *s1);
char	    **ft_split_1(char const *s, char c);
void	    *ft_memmove(void *dst, const void *src, size_t len );
void	    *ft_memcpy(void *dst, const void *src, size_t n);
int         ft_atoi(const char *str);
t_file	*ft_lstnew_file(char *file_name, int type, char *delimeter);
/*---------------ft_free.c---------------*/
void   		ft_free(char **ptr, int last); //for split
void		free_fail(t_parse_list **list); // for freeing linked list in ft_parsing file
void		free_list(t_commands *list); // for freeing linked list that each node has command ( | )
void		ft_free_split(char **ptr); // free split when it succeeds
void		ft_free_inputlist(t_parse_list **input_list); // free first step on parsing
/*---------------ft_free.c---------------*/
void		free_tokenize(t_input *token);
/*---------------parsing/ft_parsing.c---------------*/
int			ft_parsing(char *str);
/*---------------parsing/divide_cmd.c---------------*/
t_commands	*create_cmd(char *input);
/*---------------parsing/parsing_utils.c---------------*/
int			ft_strchr(const char *s, int c);
/*---------------parsing/ft_syntax.c---------------*/
int			ft_checkquotes(t_parse_list *list);
int			check_operator(char *s);
/*---------------parsing/ft_addspace.c---------------*/
void		add_space(t_commands *cmd);
/*---------------ft_split.c---------------*/
char		**ft_split(char *s);
/*---------------parsing/ft_split_cmd.c---------------*/
t_input		*split_cmd(t_commands *cmd, t_shell *shell);
/*---------------parsing/ft_split_cmd_utils.c---------------*/
void		put_delimiter(t_input *nw, char *str);
void		put_filename(t_input *nw, char *str);
void		put_cmdname(t_input *nw, char *str);
char		*remove_quotes(char *str);
int			ft_isexpanded(char *str);
/*---------------parsing/ft_split_cmdutils2.c---------------*/
char		*get_cmdname(char *s, t_shell *shell);
/*---------------parsing/expand.c---------------*/
char		*ft_expand(char *cmd, t_shell *shell);
//for signals
void		handle_ctrl_c_for_child(int sig);
void 		exit_shell(t_shell *shell, t_arg *status, int mode);
void 		remove_env(t_arg *data, t_shell *shell, char ***env, int mode);
void 		ft_str_tolower(char *str);
char		*ft_strrchr(const char *s, int c);
void 		update_shlvl(t_shell *shell);
void 		update_env_path_var(t_shell *shell, char *value, int  mode);
char		*ft_itoa(int n);
char 		*ft_getenv(char *name, char **env);
void 		add_default_env(t_shell *shell);
void 		update_inhereted_env(t_shell *shell);
int 		open_here_docs(t_shell *shell);
void		add_a_data_to_list(t_shell *shell, void *address);
void		init(t_shell **minishell, char **env);
int			ft_same_value(char *p1, char *p2);
void		copy_old_cwd(char *old_cwd, char **split_cwd);
char		*retrieve_value(t_shell *shell);
void		update_shlvl(t_shell *shell);
void 		add_update_env(t_arg *data, t_shell *shell, char ***env, int mode);
void 		ft_recover_echo(void);
void		ft_hide_ctrl_c(void);
char		*get_next_line(int fd);
int			ft_last_status(t_status *list);
void		update_cwd_list(char **split_cwd, char **split_path, int k);
int			path_is_only_levels(char **split);
int			env_exists(char *name, char **env);
void		add_new_status(t_shell *shell, int status);
void		handle_all_signals(int mode);
void		handle_signal_heredoc(int sig);
void		execute_other_commands(t_shell *shell, int mode);
int			print_all_env_vars(char **env, t_input *input);
void		echo_message(t_arg *args, t_shell *shell);
void		change_directory(t_arg *path, t_shell *shell, char ***env);
char		*find_command_path(char *s, t_shell *shell);
void		copy_list_updating(char *env_name, char *data,
				t_shell *shell, char **new_environ);
int			list_len(char **list);
int			redirect_streams(t_shell *shell);
void		pipex(t_shell *shell, int mode);
void		run_built_ins(t_shell *shell, int mode);
int			open_input_files(t_shell *shell);
char		*ft_join_args(t_arg *args);
void		declare_all_envs(char **env);
void		close_unused_here_docs(t_input *input);
int			duplicate_ends(t_shell *shell, int *ends, int pipe_count, int i);
void		close_ends_and_wait(int pipe_count, int *ends, int *processes, t_shell *shell);
int			check_path(t_arg *path, char *cwd);
int			split_values(char ***split_cwd, char ***split_path,
				char *cwd, t_arg *path);
int			copy_common_path(char **joined,
				char **split_cwd, char *delimeter);
void		copy_unique_path(char **joined, char **split_cwd,
				char **split_path, int i);
void		handle_signal_for_bin(int sig);
void		handle_quit_signal(int sig);
void 		update_oldpwd(char *old_pwd, t_shell *shell);
int			ft_is_executable(char *cmd_path);
char    	*ft_strcpy(char *s1, char *s2);
void		free_all(t_shell *minishell);
int			init_shell_struct(t_shell **minishell, char **env);
void		init_shell_environment(t_shell **minishell);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		*ft_malloc(size_t size, int flag);
void		add_a_data_to_linked_list(t_a_data **list, void *address);
char		*ft_itoa_v2(int n);
int			list_len(char **list);
void		ft_bzero(void *s, size_t n);
char		*ft_strdup_v3(const char *s1, int mode);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
int			eu_syntax_error(char *data, int mode);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strchr_occurence(const char *s, int c);
int			ft_strchr_index(const char *s, int c);
char		*ft_strtrim(char const *s1, char const *set);
int			unset_syntax_error(char *data);
int			export_syntax_error(char *data);
int			append_mode(char *data);
int			empty_args(t_arg *data);