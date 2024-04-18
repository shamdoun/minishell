CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = ./libft/ft_putstr_fd.c ./libft/ft_putchar_fd.c ./pipex/bonus/pipex_bonus.c ./pipex/bonus/pipex_utils_bonus.c ./pipex/bonus/pipex_utils2_bonus.c ./pipex/gnl/get_next_line.c ./pipex/gnl/get_next_line_utils.c ./libft/ft_split.c ./libft/ft_strjoin.c \
./libft/ft_strlen.c ./libft/ft_strncmp.c ./libft/ft_strlcat.c ./libft/ft_strlcpy.c ./libft/ft_memcpy.c execution.c built_ins.c built_ins_utils.c \
./libft/ft_atoi.c ./ft_lstadd_back_bonus.c ./ft_lstlast_bonus.c ./ft_lstnew_bonus.c ./libft/ft_strdup.c ./libft/ft_memmove.c
OBJC = $(SRCS:.c=.o) 
NAME = minishell
%.o: %.c execution.h
	${CC} ${CFLAGS} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJC}
	${CC} ${CFLAGS} minishell.c -g -lreadline ${OBJC} -o ${NAME}

clean:
	rm -f ${OBJC}

fclean: clean
	rm -f ${NAME}

re: fclean all