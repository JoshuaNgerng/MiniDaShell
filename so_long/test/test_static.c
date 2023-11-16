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
	void	*idle[3];
	void	*up[3];
	void	*down[3];
	void	*right[3];
	void	*left[3];
}	t_anime;


typedef struct s_entity
{
	void	*wall;
	void	*floor;
	void	*col[2];
	void	*exit[2];
	t_anime	ply;
	t_anime	enemy;
}	t_entity;

typedef struct s_enemy
{
	t_point ene_pos;
	char	touch_wall;
}	t_enemy;

typedef struct s_game
{
	char		**map;
	char		status;
	char		ply_move;
	int			collected;
	int			steps;
	t_point		size;
	t_point		ply_pos;
	t_point		*col_pos;
	t_enemy		*enemy;
	t_item		item;
	t_mlx		mlx;
	t_entity	entity;
}	t_game;

t_game	init(void)
{
	static t_game	g;

	return (g);
}

int main(void)
{
	t_game g;

	g = init();
	printf("test %p\n", g.col_pos);
	printf("test %p\n", g.entity.enemy.right[0]);
	printf("test %p\n", g.entity.enemy.right[1]);
	printf("test %p\n", g.entity.exit[1]);
	printf("test %p\n", g.entity.ply.up[2]);
	printf("test %d\n", g.item.col);
	printf("test %d\n", g.status);
}