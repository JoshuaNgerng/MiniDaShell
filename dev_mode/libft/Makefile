# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/17 10:24:41 by jngerng           #+#    #+#              #
#    Updated: 2023/11/17 10:49:36 by jngerng          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
OBJ_DIR = obj
SRC_DIR = src
S_NAME = ft_atoi ft_bzero ft_calloc ft_isalnum ft_isalpha ft_isascii ft_isdigit \
		ft_isprint ft_itoa ft_lstadd_back ft_lstadd_front ft_lstclear \
		ft_lstdelone ft_lstiter ft_lstlast ft_lstmap ft_lstnew ft_lstsize \
		ft_memchr ft_memcmp ft_memcpy ft_memmove ft_memset ft_putchar_fd \
		ft_putendl_fd ft_putnbr_fd ft_putstr_fd ft_split ft_strchr ft_strdup \
		ft_striteri ft_strjoin ft_strlcat ft_strlcpy ft_strlen ft_strmapi \
		ft_strncmp ft_strnstr ft_strrchr ft_strtrim ft_substr ft_tolower \
		ft_toupper get_next_line get_next_line_utils
_SRC = $(addsuffix .c, $(S_NAME))
SRC = $(addprefix $(SRC_DIR)/, $(_SRC))
OBJ = $(addprefix $(OBJ_DIR)/, $(_SRC:.c=.o))
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INC = -I includes

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

all : $(NAME)

clean:
	rm -f $(OBJ)
	if [ -d $(OBJ_DIR) ]; then rmdir $(OBJ_DIR); fi

fclean: clean
	rm -f $(NAME)

re: fclean all
