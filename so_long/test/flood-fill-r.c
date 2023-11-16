/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood-fill-r.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:02:45 by jngerng           #+#    #+#             */
/*   Updated: 2023/07/16 15:02:45 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

void	print_tab(char **area, t_point size)
{
	for (int y = 0; y < size.y; y++)
	{
		for (int x = 0; x < size.x; x++)
		{
			if (x != 0)
				printf(" ");
			printf("%c", area[y][x]);
		}
		printf("\n");
	}
}

void	flood_fill(char **tab, t_point size, t_point begin)
{
	if (begin.x < 0 || begin.y < 0)
		return ;
	if (begin.x >= size.x || begin.y >= size.y)
		return ;
	if (tab[begin.y][begin.x] == '1' || tab[begin.y][begin.x] == 'F')
		return ;
	if (tab[begin.y][begin.x] == '0')
		tab[begin.y][begin.x] = 'F';
	flood_fill(tab, size, (t_point){begin.x + 1, begin.y});
	flood_fill(tab, size, (t_point){begin.x, begin.y + 1});
	flood_fill(tab, size, (t_point){begin.x - 1, begin.y});
	flood_fill(tab, size, (t_point){begin.x, begin.y - 1});
}

char **make_area(char **zone, int _x, int _y)
{
	char **area;
	area = (char **)malloc(sizeof(char *) * _y);
	for (int i = 0; i < _y; ++i)
	{
		area[i] = (char *)malloc(sizeof(char) * _x);
		for (int j = 0; j < _x; ++j)
			area[i][j] = zone[i][2 * j];
	}
	return (area);
}

int main(void)
{
	int	i = -1;
	char *zone[] = {
		"1 1 1 1 1 1 1 1",
		"1 0 0 0 1 0 0 1",
		"1 0 0 1 0 1 0 1",
		"1 0 1 1 0 0 1 1",
		"1 1 1 0 0 1 0 1",
	};
	t_point size  = {8, 5};
	t_point begin = {4, 2};
	char **area = make_area(zone, size.x, size.y);
	print_tab(area, size);
	printf("begin\n");
	if (begin.x < size.x && begin.y < size.y && area[begin.y][begin.x] == '0')
	{
		area[begin.y][begin.x] = 'V';
		print_tab(area, size);
		area[begin.y][begin.x] = '0';
	}
	printf("after\n");
	flood_fill(area, size, begin);
	print_tab(area, size);
	while (++ i < size.y)
		free(area[i]);
	free(area);
	return (0);
}