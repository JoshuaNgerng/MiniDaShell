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
# S_NAME = main free parse expand expand2 token bash process file pipe valid utlis errmsg
S_NAME = main init input input2 check errmsg token bash free free2 utlis
_SRC = $(addsuffix .c, $(S_NAME))
SRC = $(addprefix $(SRC_DIR)/, $(_SRC))
OBJ = $(addprefix $(OBJ_DIR)/, $(_SRC:.c=.o))
CC = gcc
CFLAGS = -Wall -Wextra -Werror
CMEM = -fsanitize=address -g3
INC = -I includes -I libft/includes -Ireadline
LIBFT = -L libft -lft -lreadline

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJ)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INC) $(LIBFT)

all : $(NAME)

oclean:
	rm -f $(OBJ)
	if [-d $(OBJ_DIR)]; then rmdir $(OBJ_DIR); fi

clean: oclean
	$(MAKE) fclean -C libft

fclean: clean
	rm -f $(NAME)

re: fclean all
