#include <limits.h>
#include <readline/readline.h>
typedef struct file
{
    char	*file_name;
    int		type;
    char	*delimeter;
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
} t_shell;
