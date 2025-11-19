NAME = test_result
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Aquí listamos dónde está cada archivo
SRCS = main.c \
       ex01/ft_strncmp.c \
       ex02/ft_strcat.c \
       ex03/ft_strncat.c \
       ex04/ft_strstr.c \
       ex05/ft_strlcat.c

# Esto hace la magia
all:
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
	@echo "Compilado! Ejecuta ./${NAME}"

fclean:
	@rm -f $(NAME)

re: fclean all
