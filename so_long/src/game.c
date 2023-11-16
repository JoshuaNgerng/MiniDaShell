/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:00:42 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/16 18:30:24 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	*find_col(t_game *g, t_point p)
{
	int	i;

	i = -1;
	while (++ i < g->item.col)
	{
		if (g->col[i].pos.x == p.x && g->col[i].pos.y == p.y)
			return (g->col[i].anime[g->col[i].counter]);
	}
	return (NULL);
}

static void	image_to_window(void *mlx, void *win, t_game *g, t_point p)
{
	int	y;
	int	x;

	y = p.y * PIX_SIZE + 10;
	x = p.x * PIX_SIZE + 10;
	if (g->map[p.x][p.y] == '1')
		mlx_put_image_to_window(mlx, win, g->entity.wall, y, x);
	else if (g->map[p.x][p.y] == '0')
		mlx_put_image_to_window(mlx, win, g->entity.floor, y, x);
	else if (g->map[p.x][p.y] == 'P')
		mlx_put_image_to_window(mlx, win, g->entity.ply.idle[1], y, x);
	else if (g->map[p.x][p.y] == 'C')
		mlx_put_image_to_window(mlx, win, find_col(g, p), y, x);
	else if (g->map[p.x][p.y] == 'X')
		mlx_put_image_to_window(mlx, win, g->entity.col.exit_close[0], y, x);
	else if (g->map[p.x][p.y] == 'D')
		mlx_put_image_to_window(mlx, win, g->entity.enemy.idle[0], y, x);
}

void	*new_window(void *mlx, t_point size, char *name, t_game *g)
{
	int		i;
	int		j;
	void	*win;

	get_sprite(g);
	win = mlx_new_window(mlx, (size.y + 1) * PIX_SIZE, (size.x + 1) * PIX_SIZE, name);
	i = -1;
	while (g->map[++ i])
	{
		j = -1;
		while (g->map[i][++ j])
			image_to_window(mlx, win, g, (t_point){i, j});
	}
	return (win);
}

int	close_game(t_game *g)
{
	if (g->status == -1)
		write(1, "YOU LOSE\n", 9);
	if (g->status == 1)
		write(1, "YOU WIN\n", 8);
	mlx_destroy_window(g->mlx.init, g->mlx.win);
	free_exit(*g, 0);
	return (0);
}

int		handle_input(int key, t_game *g)
{
	if (key == ESC)
		return (close_game(g));
	if (!g->status)
	{
		if (key == UP || key == WKEY)
			ply_move_in_game(UP, g);
		if (key == DOWN || key == SKEY)
			ply_move_in_game(DOWN, g);
		if (key == LEFT || key == AKEY)
			ply_move_in_game(LEFT, g);
		if (key == RIGHT || key == DKEY)
			ply_move_in_game(RIGHT, g);
	}
	return (0);
}

// void	dev_put_map(void *mlx, void *win, t_entity e, char **map, t_point size)
// {
// 	static int	a;
// 	int			i;
// 	int			j;
	
// 	i = a / size.y;
// 	j = (a % size.y);
// 	printf("test dev a:%d i:%d j:%d\n", a, i, j);
// 	if (map[i][j] == '1')
// 		mlx_put_image_to_window(mlx, win, e.img_wall, j * PIX_SIZE + 10, i * PIX_SIZE + 10);
// 	if (map[i][j] == '0')
// 		mlx_put_image_to_window(mlx, win, e.img_floor, j * PIX_SIZE + 10, i * PIX_SIZE + 10);
// 	if (map[i][j] == 'V')
// 		mlx_put_image_to_window(mlx, win, e.img_ply, j * PIX_SIZE + 10, i * PIX_SIZE + 10);
// 	if (map[i][j] == 'O')
// 		mlx_put_image_to_window(mlx, win, e.img_col, j * PIX_SIZE + 10, i * PIX_SIZE + 10);
// 	if (map[i][j] == 'X')
// 		mlx_put_image_to_window(mlx, win, e.img_exit, j * PIX_SIZE + 10, i * PIX_SIZE + 10);
// 	printf("test char %c\n", map[i][j]);
// 	a ++;
// }

