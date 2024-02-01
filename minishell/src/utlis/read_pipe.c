/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 08:19:50 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/01 08:19:59 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_buffer(char *out, char *buffer, int r)
{
	char	*temp;

	if (r >= 0 && r <= BUFFER_SIZE)
		buffer[r] = '\0';
	else
		return (NULL);
	if (!out && !*buffer)
		return (NULL);
	if (!out)
		out = ft_strjoin(buffer, "");
	else
	{
		temp = out;
		out = ft_strjoin(out, buffer);
		free(temp);
	}
	return (out);
}

char	*read_from_pipe(int fd)
{
	int		r;
	char	*out;
	char	*buffer;

	out = NULL;
	buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	r = read(fd, buffer, BUFFER_SIZE);
	while (r > 0)
	{
		out = join_buffer(out, buffer, r);
		if (!out)
			return (free(buffer), NULL);
		r = read(fd, buffer, BUFFER_SIZE);
	}
	if (r == -1)
		return (free(buffer), NULL);
	return (free(buffer), out);
}
