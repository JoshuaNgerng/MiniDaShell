/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 16:44:02 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/16 11:43:02 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_ply_move(t_game *g, int x, int y, char move)
{
	if (g->map[x][y] == '1')
		return ;
	if (g->map[x][y] == 'X' && g->collect != g->item.col)
		return ;
	if (g->map[x][y] == 'X' && g->collect == g->item.col)
		g->status = 1;
	if (g->map[x][y] == 'C')
		g->collect ++;
	if (g->map[x][y] == 'D')
		g->status = -1;
	g->map[g->ply.pos.x][g->ply.pos.y] = '0';
	g->map[x][y] = 'P';
	g->ply.pos = (t_point){x, y};
	g->ply.move_direct = move;
	g->ply.move_status = 1;
	g->ply.counter = 0;
	g->steps ++;
	ft_putstr_fd("Player have taken ", 1);
	ft_putnbr_fd(g->steps, 1);
	ft_putendl_fd(" steps", 1);
}

void	ply_move_in_game(int move, t_game *g)
{
	if (g->ply.move_status)
		return ;
	if (move == UP)
		check_ply_move(g, g->ply.pos.x - 1, g->ply.pos.y, 'u');
	if (move == DOWN)
		check_ply_move(g, g->ply.pos.x + 1, g->ply.pos.y, 'd');
	if (move == LEFT)
		check_ply_move(g, g->ply.pos.x, g->ply.pos.y - 1, 'l');
	if (move == RIGHT)
		check_ply_move(g, g->ply.pos.x, g->ply.pos.y + 1, 'r');
	if (g->status)
		close_game(g);
}

static int	check_enemy_move(t_game *g, int index, char move, t_point new)
{
	t_point	start;

	start = g->enemy[index].pos;
	if (g->map[new.x][new.y] == '1' || g->map[new.x][new.y] == 'X')
		return (1);
	else if (g->map[new.x][new.y] == 'C')
		g->enemy->block = 1;
	else if (g->map[new.x][new.y] == 'P')
		g->status = -1;
	g->enemy[index].pos = new;
	if (g->enemy[index].block)
		g->map[start.x][start.y] = 'C';
	else
		g->map[start.x][start.y] = '0';
	g->map[new.x][new.y] = 'D';
	g->enemy[index].move_direct = move;
	g->enemy[index].move_status = 1;
	return (0);
}

int	process_enemy_move(int move, t_game *g, int num)
{
	int	out;

	out = 0;
	if (move == UP)
		out = check_enemy_move(g, num, 'u', \
					(t_point){g->enemy[num].pos.x - 1, g->enemy[num].pos.y});
	else if (move == DOWN)
		out = check_enemy_move(g, num, 'd', \
					(t_point){g->enemy[num].pos.x + 1, g->enemy[num].pos.y});
	else if (move == RIGHT)
		out = check_enemy_move(g, num, 'r', \
					(t_point){g->enemy[num].pos.x, g->enemy[num].pos.y + 1});
	else if (move == LEFT)
		out = check_enemy_move(g, num, 'l', \
					(t_point){g->enemy[num].pos.x, g->enemy[num].pos.y - 1});
	if (g->status == -1)
		close_game(g);
	return (out);
}
