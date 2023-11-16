# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/17 22:52:12 by jngerng           #+#    #+#              #
#    Updated: 2023/08/03 13:09:52 by jngerng          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
F_NAME = main utlis read map game errmsg move player art art2 animation enemy
SRC = $(foreach file, $(F_NAME), src/$(file).c)
OBJ = $(SRC:.c=.o)
INC = -I includes -I lib/includes
# MLX = -lbsd -lmlx lXext -lX11
LIB= -L lib -lft -lmlx -framework OpenGL -framework AppKit
CMEM = -fsanitize=address -g3
CFLAGS = -Wall -Wextra -Werror #$(CMEM)
CC = gcc

.c.o: includes/so_long.h
	$(CC) $(CFLAGS)  -c $< -o ${<:.c=.o} $(INC)

$(NAME): $(OBJ) includes/so_long.h
	$(MAKE) -C lib
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INC) $(LIB)

all: $(NAME)

oclean:
	rm -f $(OBJ)

clean: oclean
	$(MAKE) fclean -C lib

fclean: clean
	rm -f $(NAME)

re: fclean all

ore: oclean all