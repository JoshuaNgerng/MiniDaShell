/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood-fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:14:15 by jngerng           #+#    #+#             */
/*   Updated: 2023/07/13 18:14:15 by jngerng          ###   ########.fr       */
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

int	adj_f(char **tab, t_point in, t_point size, char a)
{
	//printf("test %d\n", in.y);
	if (in.y < 0 && in.x < 0)
		return (0);
	//printf("adj test %d %d %c\n", in.y, in.x, tab[in.y][in.x]);
	if (in.y == 0 && in.x == 0)
		if (tab[1][0] == a || tab[0][1] == a)
			return (1);
	if (in.y == 0)
		if (tab[in.y][in.x - 1] == a || tab[in.y][in.x + 1] == a || tab[in.y + 1][in.x] == a)
			return (1);
	if (in.x == 0)
		if (tab[in.y - 1][in.x] == a ||tab[in.y + 1][in.x] == a || tab[in.y][in.x + 1] == a)
			return (1);
	if (in.y > 0 && in.x > 0 && in.y < size.y - 1)
		if (tab[in.y - 1][in.x] == a ||tab[in.y + 1][in.x] == a || tab[in.y][in.x + 1] == a || tab[in.y][in.x - 1] == a)
			return (1);
	if (in.y == size.y - 1 && in.x == 0)
		if (tab[in.y][in.x + 1] == a || tab[in.y - 1][in.x] == a)
			return (1);
	if (in.y == size.y - 1 && in.x > 0)
		if (tab[in.y][in.x - 1] == a || tab[in.y][in.x + 1] == a || tab[in.y - 1][in.x] == a)
			return (1);
	return (0);
}

int	fill_line_v(char **tab, int row, int begin, int limit)
{
	int	i;
	
	i = begin;
	if (tab[i][row] == '1' || tab[i][row] == 'F')
		return (0);
	tab[i][row] = 'F';
	while (i -- > 0)
	{
		if (tab[i][row] == '1' || tab[i][row] == 'F')
			break ;
		tab[i][row] = 'F';
	}
	i = begin;
	while (++ i < limit)
	{
		if (tab[i][row] == '1' || tab[i][row] == 'F')
			break ;
		tab[i][row] = 'F';
	}
	return (1);
}

int	fill_line_h(char *tab, int begin, int limit)
{
	int	i;
	
	i = begin;
	if (tab[i] == '1' || tab[i] == 'F')
		return (0);
	tab[i] = 'F';
	while (i -- > 0)
	{
		if (tab[i] == '1' || tab[i] == 'F')
			break ;
		tab[i] = 'F';
	}
	i = begin;
	while (++ i < limit)
	{
		if (tab[i] == '1' || tab[i] == 'F')
			break ;
		tab[i] = 'F';
	}
	return (1);
}

void	intial_fill(char **tab, t_point size, t_point begin)
{
	int	i;

	i = begin.y;
	if (tab[i][begin.x] == '1')
		return ;
	fill_line_h(tab[i], begin.x, size.x);
	while (i -- > 0)
	{
		fill_line_h(tab[i], begin.x, size.x);
		if (tab[i][begin.x] == '1')
			break ;
	}
	i = begin.y;
	while (++ i < size.y)
	{
		fill_line_h(tab[i], begin.x, size.x);
		if (tab[i][begin.x] == '1')
			break ;
	}
}

int	tab_fill(char **tab, int dir, t_point size, t_point begin)
{
 	int		out;
	int		i;
	int		j;

	out = 0;
	i = -1;
	if (dir == 1)
	{
		while(++ i < size.y)
		{
			j = -1;
			while(++ j < size.x)
			{
				//printf("loop v test %d %d %c\n", i, j, tab[i][j]);
				if (tab[i][j] == '0' && adj_f(tab, (t_point){j, i}, size, 'F'))
				{
					//printf("test\n");
					if (fill_line_v(tab, j, begin.y, size.y))
						out = 1;
				}
			}
		}
	}
	else
	{
		while(++ i < size.y)
		{
			j = -1;
			while(++ j < size.x)
			{
				//printf("loop h test %d %d %c\n", i, j, tab[i][j]);
				if (tab[i][j] == '0' && adj_f(tab, (t_point){j, i}, size, 'F'))
				{
					//printf("loop in test %d %d\n", i, j);
					if (fill_line_h(tab[i], j, size.x))
						out = 1;
				}
				// printf("test h %d\n", out);
			}
		}
	}
	return (out);
}

void  flood_fill(char **tab, t_point size, t_point begin)
{
	if (begin.x >= size.x || begin.y >= size.y)
		return ;
	intial_fill(tab, size, begin);
	while (tab_fill(tab, 1, size, begin) || tab_fill(tab, 0, size, begin));
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
	int	i;
	char *zone[] = {
		"1 1 1 1 1 1 1 1",
		"1 0 0 0 1 0 0 1",
		"1 0 0 1 0 1 0 1",
		"1 0 1 1 0 0 1 1",
		"1 1 1 0 1 1 0 1",
	};
	t_point size  = {8, 5};
	t_point begin = {7, 3};
	char **area = make_area(zone, size.x, size.y);
	print_tab(area, size);
	printf("begin\n");
	if (begin.x < size.x && begin.y < size.y && area[begin.y][begin.x] == '0')
		area[begin.y][begin.x] = 'V';
	print_tab(area, size);
	printf("after\n");
	// intial_fill(area, size, begin);
	// print_tab(area, size);

	// printf("after i\n");
	flood_fill(area, size, begin);
	print_tab(area, size);
	i = -1;
	while (++ i < size.y)
		free(area[i]);
	free(area);
	return (0);
}

/*
tensorflow>=2.11.0
pyarrow==6.0.1
httplib2>=0.20.4
grpcio-status>=1.38.1
google-api-python-client>=1.8.0
apache-beam>=2.28.0
google-cloud-aiplatform[tensorboard]>=1.8.0
six==1.15.0
wget==3.2
xlrd==2.0.1
openpyxl==3.0.7
*/