NAME = mlx_test
SRC = main.c
OBJ = $(SRC:.c=.o)
INC = -I mlx
MLX = -lmlx -framework OpenGL -framework AppKit 
CFLAGS = -Wall -Wextra -Werror
CMEM = -fsanitize=address -g3
CC = gcc

%.o: %.c
	$(CC)  $(INC) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CMEM) $(OBJ) $(MLX) -o $(NAME)

clean:
	rm -f $(OBJ)
	rm -f $(NAME)
