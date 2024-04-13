CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_toupper.c ft_atoi.c ft_bzero.c \
 ft_isalnum.c ft_isalpha.c ft_isdigit.c ft_isprint.c ft_memcmp.c ft_memcpy.c \
 ft_memmove.c ft_memset.c ft_strrchr.c ft_strncmp.c ft_calloc.c \
 ft_strdup.c ft_tolower.c ft_toupper.c ft_substr.c ft_isascii.c ft_strchr.c ft_strtrim.c\
 ft_split.c ft_itoa.c ft_strnstr.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
 ft_putendl_fd.c ft_putnbr_fd.c ft_memchr.c ft_strjoin.c

SRCS_B = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
 ft_lstclear_bonus.c ft_lstiter_bonus.c

OBJECT_FILES = ${SRCS:.c=.o}
OBJECT_FILES_B = $(SRCS_B:.c=.o)
NAME = libft.a

%.o:%.c libft.h
	${CC} ${CFLAGS} -c $< -o $@

all: $(NAME)

$(NAME): $(OBJECT_FILES)
	ar rc $(NAME) $(OBJECT_FILES)

bonus: $(NAME) $(OBJECT_FILES_B)
	ar rc $(NAME) $(OBJECT_FILES_B)

clean:
	rm -f $(OBJECT_FILES) $(OBJECT_FILES_B)

fclean: clean
	rm -f $(NAME)

re: fclean all