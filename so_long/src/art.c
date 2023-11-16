/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   art.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:29:24 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/16 18:51:09 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*get_xpm(t_game g, char *fname, char *errmsg)
{
	void	*out;
	int		w;
	int		h;

	out = mlx_xpm_file_to_image(g.mlx.init, fname, &w, &h);
	if (!out)
		p(sp_err_msg(2, errmsg), free_exit(g, 1));
	return (out);
}

static void	get_ene_helper_function(t_game *g, t_anime *ptr)
{
	ptr->down[0] = get_xpm(*g, "xpm/spat_down_1.xpm", "enemy down 1");
	ptr->down[1] = get_xpm(*g, "xpm/spat_down_2.xpm", "enemy down 2");
	ptr->down[2] = get_xpm(*g, "xpm/spat_down_3.xpm", "enemy down 3");
	ptr->down[3] = get_xpm(*g, "xpm/spat_down_4.xpm", "enemy down 4");
	ptr->down[4] = get_xpm(*g, "xpm/spat_down_5.xpm", "enemy down 5");
	ptr->down[5] = get_xpm(*g, "xpm/spat_down_6.xpm", "enemy down 6");
	ptr->left[0] = get_xpm(*g, "xpm/spat_left_1.xpm", "enemy left 1");
	ptr->left[1] = get_xpm(*g, "xpm/spat_left_2.xpm", "enemy left 2");
	ptr->left[2] = get_xpm(*g, "xpm/spat_left_3.xpm", "enemy left 3");
	ptr->left[3] = get_xpm(*g, "xpm/spat_left_4.xpm", "enemy left 4");
	ptr->left[4] = get_xpm(*g, "xpm/spat_left_5.xpm", "enemy left 5");
	ptr->left[5] = get_xpm(*g, "xpm/spat_left_6.xpm", "enemy left 6");
	ptr->right[0] = get_xpm(*g, "xpm/spat_right_1.xpm", "enemy right 1");
	ptr->right[1] = get_xpm(*g, "xpm/spat_right_2.xpm", "enemy right 2");
	ptr->right[2] = get_xpm(*g, "xpm/spat_right_3.xpm", "enemy right 3");
	ptr->right[3] = get_xpm(*g, "xpm/spat_right_4.xpm", "enemy right 4");
	ptr->right[4] = get_xpm(*g, "xpm/spat_right_5.xpm", "enemy right 5");
	ptr->right[5] = get_xpm(*g, "xpm/spat_right_6.xpm", "enemy right 6");
}

static void	get_ene(t_game *g, t_anime *ptr)
{
	int	i;

	ptr->idle[0] = get_xpm(*g, "xpm/spat_idle.xpm", "enemy idle");
	ptr->idle[1] = get_xpm(*g, "xpm/spat_idle_left.xpm", "enemy idle left");
	ptr->idle[2] = get_xpm(*g, "xpm/spat_idle_right.xpm", "enemy idle right");
	ptr->up[0] = get_xpm(*g, "xpm/spat_up_1.xpm", "enemy up 1");
	ptr->up[1] = get_xpm(*g, "xpm/spat_up_2.xpm", "enemy up 2");
	ptr->up[2] = get_xpm(*g, "xpm/spat_up_3.xpm", "enemy up 3");
	ptr->up[3] = get_xpm(*g, "xpm/spat_up_4.xpm", "enemy up 4");
	ptr->up[4] = get_xpm(*g, "xpm/spat_up_5.xpm", "enemy up 5");
	ptr->up[5] = get_xpm(*g, "xpm/spat_up_6.xpm", "enemy up 6");
	get_ene_helper_function(g, ptr);
	i = -1;
	while (++ i < g->item.ene)
	{
		g->enemy[i].counter = 0;
		g->enemy[i].move_status = 0;
		g->enemy[i].move_direct = 'l';
		g->enemy[i].touch_wall = 0;
		g->enemy[i].block = 0;
	}
}

static void	get_ply(t_game *g, t_anime	*ptr)
{
	ptr->idle[0] = get_xpm(*g, "xpm/player_idle_up.xpm", "player idle up");
	ptr->idle[1] = get_xpm(*g, "xpm/player_idle_down.xpm", "player idle down");
	ptr->idle[2] = get_xpm(*g, "xpm/player_idle_right.xpm", \
								"player idle right");
	ptr->idle[3] = get_xpm(*g, "xpm/player_idle_left.xpm", "player idle left");
	ptr->up[0] = get_xpm(*g, "xpm/player_up_1.xpm", "player up 1");
	ptr->up[1] = get_xpm(*g, "xpm/player_up_2.xpm", "player up 2");
	ptr->up[2] = get_xpm(*g, "xpm/player_up_3.xpm", "player up 3");
	ptr->up[3] = get_xpm(*g, "xpm/player_up_4.xpm", "player up 4");
	ptr->up[4] = get_xpm(*g, "xpm/player_up_5.xpm", "player up 5");
	ptr->down[0] = get_xpm(*g, "xpm/player_down_1.xpm", "player down 1");
	ptr->down[1] = get_xpm(*g, "xpm/player_down_2.xpm", "player down 2");
	ptr->down[2] = get_xpm(*g, "xpm/player_down_3.xpm", "player down 3");
	ptr->down[3] = get_xpm(*g, "xpm/player_down_4.xpm", "player down 4");
	ptr->down[4] = get_xpm(*g, "xpm/player_down_5.xpm", "player down 5");
	ptr->left[0] = get_xpm(*g, "xpm/player_left_1.xpm", "player left 1");
	ptr->left[1] = get_xpm(*g, "xpm/player_left_2.xpm", "player left 2");
	ptr->left[2] = get_xpm(*g, "xpm/player_left_3.xpm", "player left 3");
	ptr->left[3] = get_xpm(*g, "xpm/player_left_4.xpm", "player left 4");
	ptr->left[4] = get_xpm(*g, "xpm/player_left_5.xpm", "player left 5");
	ptr->right[0] = get_xpm(*g, "xpm/player_right_1.xpm", "player right 1");
	ptr->right[1] = get_xpm(*g, "xpm/player_right_2.xpm", "player right 2");
	ptr->right[2] = get_xpm(*g, "xpm/player_right_3.xpm", "player right 3");
	ptr->right[3] = get_xpm(*g, "xpm/player_right_4.xpm", "player right 4");
	ptr->right[4] = get_xpm(*g, "xpm/player_right_5.xpm", "player right 5");
}

void	get_sprite(t_game *g)
{
	g->entity.wall = get_xpm(*g, "xpm/wall.xpm", "wall art");
	g->entity.floor = get_xpm(*g, "xpm/floor.xpm", "floor art");
	g->ply.counter = 0;
	g->ply.move_direct = 'd';
	get_ply(g, &(g->entity.ply));
	get_ene(g, &(g->entity.enemy));
	col_init(g);
	g->ext.anime = g->entity.col.exit_close;
}
