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
S_NAME = main env_parse env_list env_freelist freelist misc export unset #free parse token utlis errmsg
_SRC = $(addsuffix .c, $(S_NAME))
SRC = $(addprefix $(SRC_DIR)/, $(_SRC))
OBJ = $(addprefix $(OBJ_DIR)/, $(_SRC:.c=.o))
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
CMEM = -fsanitize=address -g3
INC = -I includes -I libft -Ireadline  -I/usr/local/opt/readline/include
LIBFT = -L libft -lft -lreadline -L/usr/local/opt/readline/lib

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@
#$(<:%.c=%.o)

$(NAME): $(OBJ)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INC) $(LIBFT)

all : $(NAME)

oclean:
	rm -rf $(OBJ)

clean: oclean
	$(MAKE) fclean -C libft

fclean: clean
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)

re: fclean all
