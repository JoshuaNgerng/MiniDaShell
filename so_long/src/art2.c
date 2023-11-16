/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   art2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:37:29 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/16 18:29:02 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	exit_xpm(t_game *g, t_ani_s *ptr)
{
	ptr->exit_close[0] = get_xpm(*g, "xpm/exit_close_1.xpm", "exit close 1");
	ptr->exit_close[1] = get_xpm(*g, "xpm/exit_close_2.xpm", "exit close 2");
	ptr->exit_open[0] = get_xpm(*g, "xpm/exit_open_1.xpm", "exit open art 1");
	ptr->exit_open[1] = get_xpm(*g, "xpm/exit_open_2.xpm", "exit open art 2");
	ptr->exit_open[2] = get_xpm(*g, "xpm/exit_open_3.xpm", "exit open art 3");
	ptr->exit_open[3] = get_xpm(*g, "xpm/exit_open_4.xpm", "exit open art 4");
	ptr->exit_open[4] = get_xpm(*g, "xpm/exit_open_5.xpm", "exit open art 5");
}

static void	keys_xpm(t_game *g, t_ani_s *ptr)
{
	ptr->key[0][0] = get_xpm(*g, "xpm/sun_key_1.xpm", "sun key 1");
	ptr->key[0][1] = get_xpm(*g, "xpm/sun_key_2.xpm", "sun key 2");
	ptr->key[0][2] = get_xpm(*g, "xpm/sun_key_3.xpm", "sun key 3");
	ptr->key[0][3] = ptr->key[0][1];
	ptr->key[0][4] = ptr->key[0][0];
	ptr->key[1][0] = get_xpm(*g, "xpm/moon_key_1.xpm", "moon key 1");
	ptr->key[1][1] = get_xpm(*g, "xpm/moon_key_2.xpm", "moon key 2");
	ptr->key[1][2] = get_xpm(*g, "xpm/moon_key_3.xpm", "moon key 3");
	ptr->key[1][3] = ptr->key[1][1];
	ptr->key[1][4] = ptr->key[1][0];
	ptr->key[2][0] = get_xpm(*g, "xpm/ocean_key_1.xpm", "ocean key 1");
	ptr->key[2][1] = get_xpm(*g, "xpm/ocean_key_2.xpm", "ocean key 2");
	ptr->key[2][2] = get_xpm(*g, "xpm/ocean_key_3.xpm", "ocean key 3");
	ptr->key[2][3] = ptr->key[2][1];
	ptr->key[2][4] = ptr->key[2][0];
	ptr->key[3][0] = get_xpm(*g, "xpm/rainbow_key_1.xpm", "rainbow key 1");
	ptr->key[3][1] = get_xpm(*g, "xpm/rainbow_key_2.xpm", "rainbow key 2");
	ptr->key[3][2] = get_xpm(*g, "xpm/rainbow_key_3.xpm", "rainbow key 3");
	ptr->key[3][3] = ptr->key[3][1];
	ptr->key[3][4] = ptr->key[3][0];
}

void	col_init(t_game *g)
{
	int	i;

	exit_xpm(g, &(g->entity.col));
	keys_xpm(g, &(g->entity.col));
	i = -1;
	while (++ i < g->item.col)
	{
		g->col[i].counter = i % 4;
		g->col[i].status = 0;
		if (i % 4 == 0)
			g->col[i].anime = g->entity.col.key[0];
		if (i % 4 == 1)
			g->col[i].anime = g->entity.col.key[1];
		if (i % 4 == 2)
			g->col[i].anime = g->entity.col.key[2];
		if (i % 4 == 3)
			g->col[i].anime = g->entity.col.key[3];
	}
}
