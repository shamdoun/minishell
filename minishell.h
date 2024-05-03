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

/*
	<<: 4
	>>: 2
	<: 3
	>: 1
*/

typedef struct	s_arg
{
	char			*arg;
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
}t_a_data;

typedef struct shell
{
	struct input			*all_input;
	struct status			*all_status;
	struct allocated_data	*all_allocated_data;
	char                    **env;
    char			        cwd[PATH_MAX];
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


void		ft_lst_add_input_back(t_input **lst, t_input *new);
void		ft_lst_add_ad_back(t_a_data **lst, t_a_data *new);
void		ft_lst_add_file_back(t_file **lst, t_file *new);
void		ft_lst_add_status_back(t_status **lst, t_status *new);
t_input		*ft_lstnew_input();
t_a_data	*ft_lstnew_ad(void *address);
t_status	*ft_lstnew_status(int status);
t_file	    *ft_lstnew_file(char *file_name, int type, char *delimeter);
size_t      ft_strlen(const char *);
int         ft_strncmp(const char *s1, const char *s2, size_t n);
void        execute_input(t_shell *shell);
void        free_array(char **a);
char	    *ft_strdup1(char *s);
void        print_all_env_vars(char **env);
int	        ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	    ft_strlen(const char *s);
size_t	    ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	    ft_strlcat(char *dst, const char *src, size_t dstsize);
char	    *ft_strjoin(char const *s1, char const *s2);
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
t_input		*split_cmd(t_commands *cmd);
/*---------------parsing/ft_split_cmd_utils.c---------------*/
void		put_delimiter(t_input *nw, char *str);
void		put_filename(t_input *nw, char *str);
void		put_cmdname(t_input *nw, char *str);
char		*remove_quotes(char *str);
//for signals
void        handle_signal(int sig);
void 		exit_shell(t_shell *shell, t_arg *status);
void 		remove_env(t_arg *data, t_shell *shell, char ***env);