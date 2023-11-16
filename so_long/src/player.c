/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:43:55 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/16 18:29:46 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	loop_ply_idle(t_game *g, void *anime)
{
	int	x;
	int	y;

	x = g->ply.pos.x * PIX_SIZE + 10;
	y = g->ply.pos.y * PIX_SIZE + 10;
	mlx_put_image_to_window(g->mlx.init, g->mlx.win, \
							anime, y, x);
}

void	ply_idle_anime(t_game *g)
{
	if (g->ply.move_direct == 'u')
		loop_ply_idle(g, g->entity.ply.idle[0]);
	if (g->ply.move_direct == 'd')
		loop_ply_idle(g, g->entity.ply.idle[1]);
	if (g->ply.move_direct == 'r')
		loop_ply_idle(g, g->entity.ply.idle[2]);
	if (g->ply.move_direct == 'l')
		loop_ply_idle(g, g->entity.ply.idle[3]);
}

void	loop_ply_anime(t_game *g, void **anime, t_point prev)
{
	int	y;
	int	x;

	y = (g->ply.pos.y + prev.y) / 2 * PIX_SIZE + 10;
	x = (g->ply.pos.x + prev.x) / 2 * PIX_SIZE + 10;
	mlx_put_image_to_window(g->mlx.init, g->mlx.win, \
							anime[g->ply.counter], y, x);
	g->ply.counter ++;
	if (!anime[g->ply.counter])
	{
		g->ply.move_status = 0;
		g->ply.counter = 0;
	}
}

//printf("test ply move y(%d) x(%d)\n", y, x);
//printf("test ply pos after hook y(%d), x(%d), move_status(%d), 
//move_direct(%d)\n", g->ply.pos.y, g->ply.pos.x, 
//g->ply.move_status, g->ply.move_direct);
void	ply_move_anime(t_game *g)
{
	if (g->ply.move_direct == 'u')
		loop_ply_anime(g, g->entity.ply.up, \
						(t_point){g->ply.pos.x + 1, g->ply.pos.y});
	if (g->ply.move_direct == 'd')
		loop_ply_anime(g, g->entity.ply.down, \
						(t_point){g->ply.pos.x - 1, g->ply.pos.y});
	if (g->ply.move_direct == 'r')
		loop_ply_anime(g, g->entity.ply.right, \
						(t_point){g->ply.pos.x, g->ply.pos.y - 1});
	if (g->ply.move_direct == 'l')
		loop_ply_anime(g, g->entity.ply.left, \
						(t_point){g->ply.pos.x, g->ply.pos.y + 1});
}
