/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:07:00 by jngerng           #+#    #+#             */
/*   Updated: 2023/08/03 13:21:50 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# define ESC 53
# define UP 126
# define LEFT 123
# define RIGHT 124
# define DOWN 125
# define WKEY 13
# define AKEY 0
# define DKEY 2
# define SKEY 1
# define PIX_SIZE 50
# define ANIM_TIMER 80000000
# define PLY_TIMER 50000
// int max 2147483647

typedef struct s_buffer
{
	char			*str;
	struct s_buffer	*next;
}	t_buffer;

typedef	struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_item
{
	int		ply;
	int		col;
	int		ext;
	int		ene;
}	t_item;

typedef struct s_mlx
{
	void	*init;
	void	*win;
}	t_mlx;

typedef struct s_anime
{
	void	*idle[4];
	void	*up[7];
	void	*down[7];
	void	*right[7];
	void	*left[7];
}	t_anime;

typedef struct s_ani_col
{
	void	*key[4][6];
	void	*exit_open[6];
	void	*exit_close[3];
}	t_ani_s;

typedef struct s_entity
{
	void	*wall;
	void	*floor;
	t_ani_s	col;
	t_anime	ply;
	t_anime	enemy;
}	t_entity;

typedef struct s_enemy
{
	t_point pos;
	int		counter;
	char	move_status;
	char	move_direct;
	char	touch_wall;
	char	block;
}	t_enemy;

typedef struct s_ply
{
	t_point	pos;
	int		counter;
	char	move_status;
	char	move_direct;
}	t_ply;

typedef struct s_col
{
	t_point	pos;
	int		counter;
	char	status;
	void	**anime;
}	t_col;

typedef struct s_ext
{
	t_point	pos;
	int		counter;
	int		status;
	void	**anime;
}	t_ext;


typedef struct s_game
{
	char		**map;
	char		status;
	int			collect;
	int			steps;
	t_point		size;
	t_ply		ply;
	t_ext		ext;
	t_col		*col;
	t_enemy		*enemy;
	t_item		item;
	t_mlx		mlx;
	t_entity	entity;
}	t_game;

void	*err_msg(int b);
void	*sp_err_msg(int b, char *c);
void	*p(void *f1, void *f2);
void	free_map(char **map);
void	*free_exit(t_game g, int ext_code);
t_game	game_init(void);
t_game	check_border(char *line, t_game g);
int		check_line(t_game *in, char *new_l, int n);
t_game	get_map(char *fname, t_game game);
int		valid_map(t_game *game);
void	*get_xpm(t_game g, char *fname, char *errmsg);
void	col_init(t_game *g);
void	get_sprite(t_game *g);
void	*new_window(void *mlx, t_point size, char *name, t_game *g);
int		close_game(t_game *g);
int		handle_input(int key, t_game *g);
void	ply_move_in_game(int move, t_game *g);
void	ply_idle_anime(t_game *g);
void	ply_move_anime(t_game *g);
char	enemy_move(t_game *g);
int		process_enemy_move(int move, t_game *g, int num);
void	enemy_anime(t_game *g, int i);
void	win_game(t_game *g);
int		animation(t_game *g);

void	dev_print_map(char **map);

#endif
