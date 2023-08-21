# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/08 19:12:39 by jngerng           #+#    #+#              #
#    Updated: 2023/05/08 19:12:39 by jngerng          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
S_NAME = main cmd sp utlis
SRC = $(foreach file, $(S_NAME), src/$(file).c)
B_NAME = main get_cmd pro_cmd sp utlis free_ex
B_SRC = $(foreach file, $(B_NAME), src_bonus/$(file)_bonus.c)
OBJ = $(SRC:.c=.o)
B_OBJ = $(B_SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror
CMEM = -fsanitize=address -g3
SUBDIRS = libft printf
INC = -I includes -I libft -I printf/includes

LIBFT = -L libft -lft
PRINTF = -L printf -lftprintf

.c.o:
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o} $(INC)

$(NAME): $(OBJ)
	$(MAKE) -C libft
	$(MAKE) -C printf
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INC) $(LIBFT) $(PRINTF)

all : $(NAME)

bonus: $(B_OBJ)
	$(MAKE) -C libft
	$(MAKE) -C printf
	$(CC) $(CFLAGS) -o $(NAME) $(B_OBJ) $(INC) $(LIBFT) $(PRINTF)

oclean:
	rm -f $(OBJ)

obclean:
	rm -f $(B_OBJ)

clean: oclean
	$(MAKE) fclean -C libft
	$(MAKE) fclean -C printf

fclean: clean
	rm -f libft/libft.a
	rm -f printf/libftprintf.a
	rm -f $(NAME)

re: fclean all

clean_bonus: obclean
	$(MAKE) fclean -C libft
	$(MAKE) fclean -C printf

fclean_bonus: clean_bonus
	rm -f libft/libft.a
	rm -f printf/libftprintf.a
	rm -f $(NAME)

re_bonus: fclean_bonus bonus
