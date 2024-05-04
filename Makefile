NAME = minishell
CFLAGS = -Wall -Wextra -Werror
srcs = ./execution/execution.c ./execution/redirection.c ft_lst_add_back.c ft_lstnew.c ft_strlen.c ft_memcpy.c \
ft_memmove.c ft_strlcat.c ft_strlcpy.c ft_strjoin.c ./execution/builtins/built_ins_utils.c ft_split_v2.c ft_strdup.c ft_atoi.c \
ft_strncmp.c ./execution/builtins/execute_bin.c ./execution/builtins/change_dir.c ./execution/builtins/echo.c ./execution/builtins/env.c \
./execution/builtins/exit.c ./execution/builtins/export.c ./execution/builtins/unset.c
OBJC = ${srcs:.c=.o}
%.o: %.c execution.h
	${CC} ${CFLAGS} -c $< -o $@

# all: ${NAME}

# ${NAME}: ${OBJC}
# 	${CC} ${CFLAGS} minishell.c -g -lreadline ${OBJC} -o ${NAME}

# fclean:
# 	rm -f ${OBJC}
# 	rm -f ${NAME}

#!!!!!!!!!!!!!!!!!!MAKEFILE FOR TESTING PARSING!!!!!!!!!!!!!!!!!!!!#

SRC= ft_free.c ft_split.c ./parsing/ft_parsing.c ./parsing/divide_cmd.c parsing/ft_syntax.c ft_strchr.c \
	ft_lst_add_back.c ft_lstnew.c ./parsing/ft_split_cmd.c ./parsing/ft_addspace.c \
	ft_free2.c ./parsing/ft_split_cmd_utils.c ./parsing/main.c execution/signals.c execution/execution.c execution/redirection.c execution/pipex.c \
	./execution/builtins/execute_bin.c ./execution/builtins/change_dir.c ./execution/builtins/echo.c ./execution/builtins/env.c \
	./execution/builtins/exit.c ./execution/builtins/export.c ./execution/builtins/unset.c ./execution/builtins/built_ins_utils.c ft_split_v2.c ft_strdup.c ft_atoi.c \
	ft_strncmp.c ft_strlen.c ft_strjoin.c ft_memcpy.c ft_memmove.c ft_strlcat.c ft_strlcpy.c ./parsing/ft_tolower.c ./parsing/ft_strrchr.c

CC= cc
Flags= -Wall -Werror -Wextra -g

O_SRC=$(SRC:.c=.o)

NAME= minishell 

%.o: %.c
	$(CC) $(Flags) -o $@ -c $<

all: $(NAME)

$(NAME): $(O_SRC)
	$(CC) $(FLAGS) -lreadline $(O_SRC) -o $(NAME)

clean:
	rm -f $(O_SRC)

fclean: clean
	rm -f $(NAME)

re: all clean