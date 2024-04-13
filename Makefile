CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = ./gnl/get_next_line.c ./gnl/get_next_line_utils.c ./libft/ft_putstr_fd.c ./libft/ft_putchar_fd.c
OBJC = $(SRCS:.c=.o) 
NAME = minishell
%.o: %.c execution.h
	${CC} ${CFLAGS} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJC}
	${CC} ${CFLAGS} minishell.c -lreadline ${OBJC} -o ${NAME}

clean:
	rm -f ${OBJC}

fclean: clean
	rm -f ${NAME}

