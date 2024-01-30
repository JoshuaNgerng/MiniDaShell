/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:35:48 by jngerng           #+#    #+#             */
/*   Updated: 2024/01/30 16:32:48 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_free(DIR *d, t_token *buffer)
{
	closedir(d);
	free_tokens(buffer);
}

char	*join_buffer_star(t_token *head, int len)
{
	int		i;
	char	*out;
	t_token	*ptr;

	out = (char *) malloc((len + 1) * sizeof(char));
	if (!out)
		return (NULL);
	// printf("test len %d\n", len);
	i = 0;
	ptr = head;
	while (ptr)
	{
		i = int_strcpy(out, i, ptr->token);
		// printf("testing %s\n", ptr->token);
		out[i ++] = ' ';
		// out[i] = '\0';
		// printf("test |%s|\n", out);
		// printf("test index %d\n", i);
		ptr = ptr->next;
	}
	out[i - 1] = '\0';
	// printf("test index %d\n", i - 1);
	// printf("testing fin %s\n", out);
	return (out);
}

int	read_star(t_star *s, t_token *new, int *ptr)
{
	int				len;
	DIR				*d;
	char			*dir;
	t_ptr			buffer;//

	len = 0;
	dir = ".";
	new->token = NULL;
	buffer = (t_ptr){NULL, NULL};
	if (s->head_type)
	{
		dir = &s->str[s->start];
		s->str[s->star_pos - 1] = '\0';
	}
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
