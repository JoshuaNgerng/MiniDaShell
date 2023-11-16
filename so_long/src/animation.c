/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 05:05:01 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/16 19:01:08 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	loop_col(t_game *g)
{
	int	i;
	int	x;
	int	y;

	i = -1;
	while (++ i < g->item.col)
	{
		if (g->map[g->col[i].pos.x][g->col[i].pos.y] != 'C')
			continue ;
		g->col[i].counter ++;
		if (!g->col[i].anime[g->col[i].counter])
			g->col[i].counter = 0;
		x = g->col[i].pos.x * PIX_SIZE + 10;
		y = g->col[i].pos.y * PIX_SIZE + 10;
		mlx_put_image_to_window(g->mlx.init, g->mlx.win, \
								g->col[i].anime[g->col[i].counter], y, x);
	}
}

static void	loop_exit(t_game *g)
{
	int	x;
	int	y;

	if (!g->ext.status)
	{
		if (g->collect == g->item.col)
		{
			g->ext.anime = g->entity.col.exit_open;
			g->ext.status = 1;
			g->ext.counter = -1;
		}
	}
	g->ext.counter ++;
	if (!g->ext.anime[g->ext.counter])
		g->ext.counter = 0;
	x = g->ext.pos.x * PIX_SIZE + 10;
	y = g->ext.pos.y * PIX_SIZE + 10;
	mlx_put_image_to_window(g->mlx.init, g->mlx.win, \
							g->ext.anime[g->ext.counter], y, x);
}

int	animation(t_game *g)
{
	int	i;

	i = 0;
	// while (i < 547483647)
	// 	i ++;
	while (i < ANIM_TIMER)
		i ++;
	if (!g->ply.move_status)
		ply_idle_anime(g);
	else
		ply_move_anime(g);
	i = -1;
	while (++ i < g->item.ene)
		enemy_anime(g, i);
	loop_col(g);
	loop_exit(g);
	return (0);
}
