/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:35:48 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/01 10:28:10 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_free(DIR *d, t_token *buffer)
{
	closedir(d);
	free_tokens(buffer);
}

static char	*join_buffer_star(t_token *head, int len)
{
	int		i;
	char	*out;
	t_token	*ptr;

	out = (char *) malloc((len + 1) * sizeof(char));
	if (!out)
		return (errmsg_errno(18), NULL);
	i = 0;
	ptr = head;
	while (ptr)
	{
		i = int_strcpy(out, i, ptr->token);
		out[i ++] = ' ';
		ptr = ptr->next;
	}
	out[i - 1] = '\0';
	return (out);
}

static char	*dir_init(t_star *s)
{
	s->str[s->star_pos - 1] = '\0';
	return (&s->str[s->start]);
}

int	read_star(t_star *s, t_token *new, int *ptr)
{
	int		len;
	DIR		*d;
	char	*dir;
	t_ptr	buffer;

	len = 0;
	dir = ".";
	new->token = NULL;
	buffer = (t_ptr){NULL, NULL};
	if (s->head_type)
		dir = dir_init(s);
	d = opendir(dir);
	if (!d)
		return (0);
	if (read_from_dir(s, d, &buffer, &len))
		return (close_free(d, buffer.head), 1);
	if (!buffer.head)
		return (close_free(d, buffer.head), 0);
	new->token = join_buffer_star(buffer.head, len);
	if (!new->token)
		return (close_free(d, buffer.head), 1);
	*ptr = len;
	return (close_free(d, buffer.head), 0);
}
