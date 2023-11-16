/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:58:16 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/16 16:39:29 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_buffer_list(t_buffer **head)
{
	t_buffer	*f_ptr;
	t_buffer	*n_ptr;

	if (!head)
		return;
	n_ptr = *head;
	while (n_ptr)
	{
		f_ptr = n_ptr;
		n_ptr = n_ptr->next;
		if (f_ptr->str)
			free(f_ptr->str);
		free(f_ptr);
	}
	*head = NULL;
}

static int	read_map_helper(t_buffer **head, int fd)
{
	int			size;
	char		*r;
	t_buffer	*temp;
	t_buffer	*new;

	size = 1;
	temp = *head;
	while (1)
	{
		r = get_next_line(fd);
		if (!r)
		{
			temp->next = NULL;
			if (errno == ENOMEM)
				return (free_buffer_list(head), -1);
			return (size);
		}
		new = (t_buffer *) malloc (sizeof(t_buffer));
		temp->next = new;
		if (!new)
			return (free(r), free_buffer_list(head), sp_err_msg(3, NULL), -1);
		new->str = r;
		temp = temp->next;
		size ++;
	}
	return (0);
}

static t_buffer	*read_map(int fd, int *ptr)
{
	char		*r;
	t_buffer	*head;

	r = get_next_line(fd);
	if (!r)
	{
		if (errno == ENOMEM)
			return (sp_err_msg(4, NULL), NULL);
		return (err_msg(12), NULL);
	}
	head = (t_buffer *) malloc (sizeof(t_buffer));
	if (!head)
		return (free(r), sp_err_msg(3, NULL), NULL);
	head->str = r;
	head->next = NULL;
	*ptr = read_map_helper(&head, fd);
	if (*ptr < 0)
		head = NULL;
	return (head);
}

static char	**make_map(t_buffer *buffer, int size)
{
	int		i;
	char	**out;

	out = (char **) malloc ((size + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	i = -1;
	while (++ i < size)
	{
		out[i] = buffer->str;
		buffer->str = NULL;
		buffer = buffer->next;
	}
	out[i] = NULL;
	return (out);
}

t_game	get_map(char *fname, t_game game)
{
	int			i;
	int			fd;
	t_buffer	*buffer;

	i = -1;
	fd = open(fname, O_RDONLY);
	if (fd < 0)
	{
		sp_err_msg(5, NULL);
		exit(1);
	}
	buffer = read_map(fd, &game.size.x);
	close(fd);
	if (!buffer)
		exit(1);
	game.map = make_map(buffer, game.size.x);
	free_buffer_list(&buffer);
	if (!game.map)
		exit(1);
	game = check_border(game.map[0], game);
	while (++ i < game.size.x - 1)
	{
		if (check_line(&game, game.map[i], i))
			free_exit(game, 1);
	}
	check_border(game.map[i], game);
	return (game);
}
