# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/13 23:34:59 by shamdoun          #+#    #+#              #
#    Updated: 2024/03/19 21:23:36 by shamdoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = pipex.c pipex_utils.c
OBJC = $(SRCS:.c=.o) 
SRC_B = ./bonus/pipex_bonus.c ./bonus/pipex_utils_bonus.c ./bonus/pipex_utils2_bonus.c ./gnl/get_next_line.c ./gnl/get_next_line_utils.c
OBJC_B = $(SRC_B:.c=.o)
NAME = pipex

LIBFT = libft.a
LIBFT_D = ./libft
LIBFT_P  = $(LIBFT_D)/$(LIBFT)

%.o:%.c pipex.h pipex_bonus.h
	CC $(C_FLAGS) -c $< -o $@

all: ${NAME}

${NAME}: ${OBJC} ${LIBFT_P}
	${CC} ${C_FLAGS} ${OBJC} ${LIBFT_P} -o ${NAME}

${LIBFT_P}:
	@cd ${LIBFT_D} && $(MAKE)

bonus: ${OBJC_B} $(LIBFT_P)
	$(CC) $(C_FLAGS) $(OBJC_B) $(LIBFT_P) -o ${NAME}

clean:
	@cd ${LIBFT_D} && ${MAKE} clean
	rm -f $(OBJC) $(OBJC_B)

fclean: clean
	@cd ${LIBFT_D} && ${MAKE} fclean
	rm -f $(NAME)

re: fclean all