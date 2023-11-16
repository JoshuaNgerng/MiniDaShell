/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:46:09 by jngerng           #+#    #+#             */
/*   Updated: 2023/08/02 15:28:37 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_enemy	*get_enemy(t_game g)
{
	t_point	p;
	int		i;

	p.x = -1;
	i = -1;
	while (g.map[++ p.x])
	{
		p.y = -1;
		while (g.map[p.x][++ p.y])
		{
			if (g.map[p.x][p.y] == 'D')
			{
				g.enemy[++ i].pos = p;
				g.enemy[i].touch_wall = 0;
			}
		}
	}
	return (g.enemy);
}

static t_item	flood_fill(char **map, t_point start, t_item t, t_game *g)
{
	if (start.x < 0 || start.y < 0 || ft_checkset(map[start.x][start.y], "1FX"))
		return (t);
	if (ft_checkset(map[start.x][start.y], "0PD"))
		map[start.x][start.y] = 'F';
	if (map[start.x][start.y] == 'C')
	{
		g->col[t.col].pos = (t_point){start.x, start.y};
		t.col ++;
		map[start.x][start.y] = 'F';
	}
	if (map[start.x][start.y] == 'E')
	{
		t.ext ++;
		g->ext.pos = (t_point){start.x, start.y};
		map[start.x][start.y] = 'X';
		return (t);
	}
	t = flood_fill(map, (t_point){start.x + 1, start.y}, t, g);
	t = flood_fill(map, (t_point){start.x, start.y + 1}, t, g);
	t = flood_fill(map, (t_point){start.x - 1, start.y}, t, g);
	t = flood_fill(map, (t_point){start.x, start.y - 1}, t, g);
	return (t);
}

static char	**restore_map(char **map, t_game g)
{
	int	i;
	int	j;

	i = -1;
	while (map[++ i])
	{
		j = -1;
		while (map[i][++ j])
		{
			if (map[i][j] == 'F')
				map[i][j] = '0';
		}
	}
	map[g.ply.pos.x][g.ply.pos.y] = 'P';
	i = -1;
	while (++ i < g.item.col)
		map[g.col[i].pos.x][g.col[i].pos.y] = 'C';
	i = -1;
	while (++ i < g.item.ene)
		map[g.enemy[i].pos.x][g.enemy[i].pos.y] = 'D';
	return (map);
}

int	valid_map(t_game *game)
{
	t_item	reach;

	if (!game->map)
		return (1);
	if (game->size.y == game->size.x)
		return (err_msg(4), 1);
	if (game->item.ply == 0)
		return (err_msg(5), 1);
	if (game->item.ply > 1)
		return (err_msg(6), 1);
	if (game->item.ext != 1)
		return (err_msg(7), 1);
	if (game->item.col == 0)
		return (err_msg(8), 1);
	if (game->item.ene > 0)
		game->enemy = get_enemy(*game);
	reach = flood_fill(game->map, game->ply.pos, (t_item){0, 0, 0, 0}, game);
	if (reach.col != game->item.col)
		return (err_msg(9), 1);
	if (reach.ext != game->item.ext)
		return (err_msg(10), 1);
	game->map = restore_map(game->map, *game);
	return (0);
}
