NAME = minishell
CFLAGS = -Wall -Wextra -Werror
srcs = ./execution/execution.c ./execution/redirection.c ft_lst_add_back.c ft_lstnew.c ft_strlen.c ft_memcpy.c \
ft_memmove.c ft_strlcat.c ft_strlcpy.c ft_strjoin.c ./execution/builtins/built_ins_utils.c ft_split.c ft_strdup.c \
ft_strncmp.c ./execution/builtins/execute_bin.c
OBJC = ${srcs:.c=.o}
%.o: %.c execution.h
	${CC} ${CFLAGS} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJC}
	${CC} ${CFLAGS} minishell.c -g -lreadline ${OBJC} -o ${NAME}

fclean:
	rm -f ${OBJC}
	rm -f ${NAME}
