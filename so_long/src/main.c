/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 22:53:22 by jngerng           #+#    #+#             */
/*   Updated: 2023/08/03 15:09:21 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	game_entity_init(t_game *game, char *fname)
{
	char	*ptr;

	game->col = (t_col *) malloc (game->item.col * sizeof(t_col));
	if (!game->col)
		p(sp_err_msg(1, "col (malloc): "), free_exit(*game, 1));
	if (game->item.ene > 0)
	{
		game->enemy = (t_enemy *) malloc (game->item.ene * sizeof(t_enemy));
		if (!game->enemy)
			p(sp_err_msg(1, "enemy (malloc): "), free_exit(*game, 1));
	}
	ptr = strchr(fname, '.');
	*ptr = '\0';
}

static int	check_file(char *name)
{
	char	*ptr;
	int		l;

	ptr = ft_strrchr(name, '.');
	if (!ptr)
		return (1);
	l = ft_strlen(ptr);
	if (l != 4)
		return (1);
	if (ft_strncmp(ptr, ".ber", l))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	game = game_init();
	if (ac != 2)
		return (err_msg(0), 0);
	if (check_file(av[1]))
		return (err_msg(1), 1);
	game = get_map(av[1], game);
	if (!game.map)
		return (1);
	game_entity_init(&game, av[1]);
	if (valid_map(&game))
		return (free_map(game.map), 1);
	// dev_print_map(game.map);
	game.mlx.init = mlx_init();
	if (!game.mlx.init)
		return (err_msg(11), free_map(game.map), 1);
	game.mlx.win = new_window(game.mlx.init, game.size, av[1], &game);
	mlx_hook(game.mlx.win, 17, (1L << 0), &close_game, &game);
	mlx_key_hook(game.mlx.win, &handle_input, &game);
	mlx_loop_hook(game.mlx.init, &animation, &game);
	// mlx_loop_hook(game.mlx.init, &col_anime, &game);
	// mlx_loop_hook(game.mlx.init, int (*f)(), void *param);
	mlx_loop(game.mlx.init);
	// system("leaks so_long");
	if (game.enemy)
		free(game.enemy);
	return (free_map(game.map), free(game.col), 0);
}
