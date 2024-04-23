#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <libc.h>
#include <stdbool.h>

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
	char			*args;
	struct file		*all_files;
	int				in_file;
	int				out_file;
	char			cwd[PATH_MAX];
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
} t_shell;


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
char	    **ft_split(char const *s, char c);
void	    *ft_memmove(void *dst, const void *src, size_t len );
void	    *ft_memcpy(void *dst, const void *src, size_t n);
int         ft_atoi(const char *str);

