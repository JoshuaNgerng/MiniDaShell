/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:19:29 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/16 19:04:38 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_wall(char **map, int *wall, t_point p, int i)
{
	if (map[p.x - i][p.y] == '1' || map[p.x - i][p.y] == 'X')
		wall[0] = 1;
	if (map[p.x + i][p.y] == '1' || map[p.x + i][p.y] == 'X')
		wall[1] = 1;
	if (map[p.x][p.y - i] == '1' || map[p.x][p.y - i] == 'X')
		wall[2] = 1;
	if (map[p.x][p.y + i] == '1' || map[p.x][p.y + i] == 'X')
		wall[3] = 1;
}

char	check_nearby_ply(t_game g, t_point p)
{
	int	limit;
	int	i;
	int	wall[4];

	limit = 5;
	i = -1;
	ft_bzero(wall, 4 * sizeof(int));
	while (++ i < limit)
	{
		if (p.x - i > 0)
			if (g.map[p.x - i][p.y] == 'P' && !wall[0])
				return ('u');
		if (p.x + i < g.size.x)
			if (g.map[p.x + i][p.y] == 'P' && !wall[1])
				return ('d');
		if (p.y - i > 0)
			if (g.map[p.x][p.y - i] == 'P' && !wall[2])
				return ('l');
		if (p.x + i < g.size.y)
			if (g.map[p.x][p.y + i] == 'P' && !wall[3])
				return ('r');
		check_wall(g.map, wall, p, i);
	}
	return (0);
}

char	calm_patrol_loop(t_game *g, int num)
{
	char	m;
	// int		move;

	m = 'l';
	if (!process_enemy_move(LEFT, g, num))
	{
		m = 'r';
		g->enemy[num].touch_wall ++;
		if (!process_enemy_move(RIGHT, g, num))
		{
			m = 'u';
			g->enemy[num].touch_wall ++;
			if (!process_enemy_move(UP, g, num))
			{
				m = 'd';
				g->enemy[num].touch_wall ++;
				if (!process_enemy_move(DOWN, g, num))
					g->enemy[num].touch_wall ++;
			}
		}
	}
	if (g->enemy[num].touch_wall == 4)
		g->enemy[num].touch_wall = 0;
	return (m);
}

void	loop_anime(t_game *g, int i, void **anime, t_point prev)
{
	int	y;
	int	x;

	y = (g->enemy[i].pos.y + prev.y) / 2 * PIX_SIZE + 10;
	x = (g->enemy[i].pos.x + prev.x) / 2 * PIX_SIZE + 10;
	mlx_put_image_to_window(g->mlx.init, g->mlx.win, \
							anime[g->ply.counter], y, x);
	g->enemy[i].counter ++;
	if (!anime[g->enemy[i].counter])
	{
		g->enemy[i].move_status = 0;
		g->enemy[i].counter = 0;
	}
}

void	enemy_anime(t_game *g, int i)
{
	printf("test1 enemy\n");
	if (!g->enemy[i].move_status)
	{
		printf("test2 enemy\n");
		g->enemy[i].move_direct = check_nearby_ply(*g, g->enemy[i].pos);
		if (!g->enemy[i].move_direct)
			g->enemy[i].move_direct = calm_patrol_loop(g, i);
		else
			process_enemy_move(g->enemy[i].move_direct, g, i);
		g->enemy[i].move_status = 1;
		g->enemy[i].counter = -1;
	}
	printf("test3 enemy\n");
	if (g->enemy[i].move_direct == 'u')
		loop_anime(g, i, g->entity.enemy.up, \
					(t_point){g->enemy[i].pos.x + 1, g->enemy[i].pos.y});
	if (g->enemy[i].move_direct == 'd')
		loop_anime(g, i, g->entity.enemy.down, \
					(t_point){g->enemy[i].pos.x - 1, g->enemy[i].pos.y});
	if (g->enemy[i].move_direct == 'r')
		loop_anime(g, i, g->entity.enemy.right, \
					(t_point){g->enemy[i].pos.x, g->enemy[i].pos.y - 1});
	if (g->enemy[i].move_direct == 'l')
		loop_anime(g, i, g->entity.enemy.left, \
					(t_point){g->enemy[i].pos.x, g->enemy[i].pos.y + 1});
}
