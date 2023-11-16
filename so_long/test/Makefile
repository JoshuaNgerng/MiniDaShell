NAME = mlx_test
SRC = mlx.c
OBJ = mlx.o
INC = -I ../mlx
MLX = -L ../mlx -lmlx -lXext -lX11 -lm -lz
CFLAGS = -Wall -Wextra -Werror
CC = gcc
CMEM = -fsanitize=address -g3

.c.o:
	$(CC) -O3 -c $< -o ${<:.c=.o} $(INC)

$(NAME): $(OBJ)
	$(CC) $(CMEM) -o $(NAME) $(OBJ) $(INC) $(MLX)

all: $(NAME)

clean:
	rm $(OBJ)

fclean: clean
	rm $(NAME)