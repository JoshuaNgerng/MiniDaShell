/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errmsg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:28:27 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/16 11:22:10 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*err_msg(int b)
{
	write(2, "Error\n", 6);
	if (b == 0)
		write(2, "Wrong number of arugments\n", 26);
	else if (b == 1)
		write(2, "Invalid filename, does have .ber extension\n", 43);
	else if (b == 2)
		write(2, "File cannot be opened\n", 22);
	else if (b == 3)
		write(2, "Map needs to be closed/surrounded by walls (1)\n", 47);
	else if (b == 4)
		write(2, "Map must be rectangular shape\n", 30);
	else if (b == 5)
		write(2, "Player not found (P)\n", 21);
	else if (b == 6)
		write(2, "More than one player (P)\n", 25);
	else if (b == 7)
		write(2, "No exit found (E)\n", 18);
	else if (b == 8)
		write(2, "No collectable found (C)\n", 25);
	else if (b == 9)
		write(2, "Not all collectable (C) are reachable\n", 38);
	else if (b == 10)
		write(2, "Exit is not reachable\n", 22);
	else if (b == 11)
		write(2, "Minilibx fail to initialize\n", 28);
	else if (b == 12)
		write(2, "Empty Map\n", 10);
	return (NULL);
}

void	*sp_err_msg(int b, char *c)
{
	char	*ptr;

	write(2, "Error\n", 6);
	if (b == 0)
	{
		write(2, "Invalid character in map, ", 26);
		write(2, c, 1);
	}
	else if (b == 1)
		write(2, c, ft_strlen(c));
	else if (b == 2)
	{
		write(2, c, ft_strlen(c));
		write(2, ": ", 2);
	}
	else if (b == 3)
		write(2, "t_buffer (malloc): ", 19);
	else if (b == 4)
		write(2, "get_next_line (malloc): ", 24);
	else if (b == 5)
		write(2, "File cannot be opened: ", 23);
	if (errno)
	{
		ptr = strerror(errno);
		write(2, ptr, ft_strlen(ptr));
	}
	write(2, "\n", 1);
	return (NULL);
}

void	*p(void *f1, void *f2)
{
	(void)f1;
	(void)f2;
	return (NULL);
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = -1;
	while (map[++ i])
		free(map[i]);
	free(map);
}

void	*free_exit(t_game g, int ext_code)
{
	free_map(g.map);
	if (g.enemy)
		free(g.enemy);
	if (g.col)
		free(g.col);
	system("leaks so_long");
	exit(ext_code);
	return (NULL);
}