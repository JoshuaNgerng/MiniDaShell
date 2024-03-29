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
S_NAME = main
DIR_U = utlis
S_NAME_U = env free free2 free3 free4 misc pipes string
DIR_INPUT = input
S_NAME_INPUT = check_input check_loop loop_input check_token
DIR_INIT = init
S_NAME_INIT = init prompt sig
DIR_HD = heredoc
S_NAME_HD = here_doc_init here_doc_wrt
DIR_EX = expand
S_NAME_EX = expand_cmd expand_search expand_copy \
			expand_root expand_heredoc expand_star
DIR_STAR = star
S_NAME_STAR = star readdir
DIR_ERR = errmsg
S_NAME_ERR = errmsg errmsg_err
DIR_CHILD = child
S_NAME_CHILD = child cmd file subshell
DIR_BUILT = builtin
S_NAME_BUILT = builtin export unset cd echo builtin_err
DIR_BASH = bash
S_NAME_BASH = bash_start section tokenize process preproc
SRC_MAIN = $(foreach item, $(S_NAME), $(SRC_DIR)/$(item).c)
SRC_U = $(foreach item, $(S_NAME_U), $(SRC_DIR)/$(DIR_U)/$(item).c)
SRC_INPUT = $(foreach item, $(S_NAME_INPUT), $(SRC_DIR)/$(DIR_INPUT)/$(item).c)
SRC_INIT = $(foreach item, $(S_NAME_INIT), $(SRC_DIR)/$(DIR_INIT)/$(item).c)
SRC_HD = $(foreach item, $(S_NAME_HD), $(SRC_DIR)/$(DIR_HD)/$(item).c)
SRC_EX = $(foreach item, $(S_NAME_EX), $(SRC_DIR)/$(DIR_EX)/$(item).c)
SRC_STAR = $(foreach item, $(S_NAME_STAR), $(SRC_DIR)/$(DIR_STAR)/$(item).c)
SRC_ERR = $(foreach item, $(S_NAME_ERR), $(SRC_DIR)/$(DIR_ERR)/$(item).c)
SRC_CHILD = $(foreach item, $(S_NAME_CHILD), $(SRC_DIR)/$(DIR_CHILD)/$(item).c)
SRC_BUILT = $(foreach item, $(S_NAME_BUILT), $(SRC_DIR)/$(DIR_BUILT)/$(item).c)
SRC_BASH = $(foreach item, $(S_NAME_BASH), $(SRC_DIR)/$(DIR_BASH)/$(item).c)
SRC_SUB = $(foreach item, $(S_NAME_SUB), $(SRC_DIR)/$(DIR_SUB)/$(item).c)
S_NAME_DEV = dev
DIR_DEV = utlis
SRC_DEV = $(foreach item, $(S_NAME_DEV), $(SRC_DIR)/$(DIR_DEV)/$(item).c)
S_LIST = $(S_NAME) $(S_NAME_U) $(S_NAME_INPUT) $(S_NAME_INIT) $(S_NAME_HD) $(S_NAME_EX) $(S_NAME_STAR) \
		$(S_NAME_ERR) $(S_NAME_CHILD) $(S_NAME_BUILT) $(S_NAME_BASH) $(S_NAME_SUB) $(S_NAME_DEV)
OBJ = $(foreach item, $(S_LIST), $(OBJ_DIR)/$(item).o)
CC = gcc
CMEM = -fsanitize=address -g3
CFLAGS = -Wall -Wextra -Werror $(CMEM)
INC = -I includes -I libft/includes -I readline -I /usr/local/opt/readline/include
LIBFT = -L libft -lft -lreadline -lncurses -L /usr/local/opt/readline/lib

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(DIR_SUB)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(DIR_BASH)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(DIR_BUILT)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(DIR_CHILD)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(DIR_ERR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(DIR_STAR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(DIR_EX)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(DIR_HD)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(DIR_INIT)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(DIR_INPUT)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(DIR_U)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJ)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INC) $(LIBFT)

all : $(NAME)

ifeq ($(wildcard $(OBJ_DIR)),)

oclean:
	rm -f $(OBJ)

else

oclean:
	rm -f $(OBJ)
	rmdir $(OBJ_DIR)

endif

clean: oclean
	$(MAKE) fclean -C libft

fclean: clean
	rm -f $(NAME)

re: fclean all
