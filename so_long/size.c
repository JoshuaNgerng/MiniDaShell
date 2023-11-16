#include <stdio.h>

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

int	main(void)
{
	printf("%s, size:%ld\n", "t_game", sizeof(t_game));
	printf("%s, size:%ld\n", "t_ext", sizeof(t_ext));
	printf("%s, size:%ld\n", "t_point", sizeof(t_point));
	return (0);
}