CFLAGS = -Wall -Werror -Wextra

srcs = ./execution/execution.c ./execution/builtins/change_dir.c ./execution/builtins/export.c ./execution/builtins/env.c ./execution/builtins/echo.c \
 ./execution/builtins/built_ins_utils.c ./execution/builtins/execute_bin.c ft_lst_add_back.c ./execution/builtins/unset.c ./execution/builtins/exit.c ./libft/ft_atoi.c \
 ft_lstnew.c ft_strlen.c ./libft/ft_strncmp.c ./libft/ft_split.c ./libft/ft_strdup.c ./libft/ft_strjoin.c ./libft/ft_memcpy.c ./libft/ft_strlcat.c \
 ./libft/ft_strlcpy.c ./libft/ft_memmove.c
objc = ${srcs:.c=.o}

%.o:%.c minishell.h
	cc ${CFLAGS} -c $< -o $@


all: ${objc}
	cc ${CFLAGS} -g -lreadline ${srcs} minishell.c -o minishell

fclean:
	rm -f ${objc}
	rm -f minishell