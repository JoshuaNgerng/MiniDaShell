# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/22 15:43:55 by jngerng           #+#    #+#              #
#    Updated: 2023/08/22 15:43:55 by jngerng          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
OBJ_DIR = obj
SRC_DIR = src
S_NAME = main free parse token bash process file pipe valid utlis errmsg
_SRC = $(addsuffix .c, $(S_NAME))
SRC = $(addprefix $(SRC_DIR)/, $(_SRC))
OBJ = $(addprefix $(OBJ_DIR)/, $(_SRC:.c=.o))
CC = gcc
CFLAGS = -Wall -Wextra -Werror
CMEM = -fsanitize=address -g3
INC = -I includes -I lib/includes -Ireadline
LIBFT = -L lib -lft -lreadline

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@
#$(<:%.c=%.o)

$(NAME): $(OBJ)
	$(MAKE) -C lib
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INC) $(LIBFT)

all : $(NAME)

oclean:
	rm -f $(OBJ)

clean: oclean
	$(MAKE) fclean -C lib

fclean: clean
	rmdir $(OBJ_DIR)
	rm -f $(NAME)

re: fclean all
