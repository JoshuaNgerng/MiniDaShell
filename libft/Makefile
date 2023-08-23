# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/12 19:44:19 by mukhairu          #+#    #+#              #
#    Updated: 2023/06/06 15:51:45 by mukhairu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c \
	ft_isascii.c ft_isprint.c ft_strlen.c \
	ft_memset.c ft_bzero.c ft_memcpy.c \
	ft_memmove.c ft_strlcpy.c ft_strlcat.c \
	ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strncmp.c ft_memchr.c ft_memcmp.c \
	ft_strnstr.c ft_atoi.c ft_calloc.c \
	ft_strdup.c ft_substr.c ft_strjoin.c \
	ft_strtrim.c ft_split.c ft_itoa.c \
	ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
	ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_strrchr.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
	ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
	ft_lstclear.c ft_lstiter.c ft_lstmap.c

MAIN_SRC = $(addprefix obj/, $(SRC:.c=.o))

NAME = libft.a

CC = gcc

AR = ar -crs

RM = rm -rf

INCLUDES = libft.h

CFLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(MAIN_SRC)
	@$(AR) $(NAME) $(MAIN_SRC)
	@echo "Libft Mandatory done"

obj/%.o: %.c $(INCLUDES) | obj
	@$(CC) $(CFLAGS) -c $< -o $@ -I .

obj:
	@mkdir -p obj

clean:
	@$(RM) $(MAIN_SRC)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) obj

re: fclean all
