/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readdir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 01:45:02 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/01 10:32:42 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_file(const t_star *s, const char *fname, int len)
{
	int	n;

	n = s->end - s->star_pos;
	if ((s->head_type || s->start == s->star_pos) && s->end != s->star_pos)
	{
		if (!ft_strncmp(&fname[len - n], &s->str[s->star_pos + 1], n))
			return (0);
	}
	else if (!s->head_type && s->start != s->star_pos && s->end == s->star_pos)
	{
		if (!ft_strncmp(fname, &s->str[s->start], s->star_pos - s->start))
			return (0);
	}
	else if (s->end != s->star_pos)
	{
		if (!ft_strncmp(&fname[len - n], &s->str[s->star_pos + 1], n) && \
			!ft_strncmp(fname, &s->str[s->start], s->star_pos - s->start))
			return (0);
	}
	else
		return (0);
	return (1);
}

static char	*strjoin_dir(const char *dir, const char *fname)
{
	int		i;
	int		len;
	int		len2;
	char	*out;

	len = ft_strlen(dir);
	len2 = ft_strlen(fname);
	out = (char *) malloc((len + len2 + 2) * sizeof(char));
	if (!out)
		return (NULL);
	i = int_strcpy(out, 0, dir);
	out[i ++] = '/';
	i = int_strcpy(out, i, fname);
	out[i] = '\0';
	return (out);
}

static int	process_file(const char *dir, const char *fname,
						t_ptr *buffer, int type)
{
	t_token	*new;

	new = (t_token *) malloc(sizeof(t_token));
	if (!new)
		return (1);
	if (type)
		new->token = strjoin_dir(dir, fname);
	else
		new->token = ft_strdup(fname);
	if (!new->token)
		return (free(new), 1);
	transfer_token_ptr(buffer, new);
	return (0);
}

int	read_from_dir(t_star *s, DIR *d, t_ptr *buffer, int *len_ptr)
{
	int				len;
	struct dirent	*dir;

	dir = readdir(d);
	while (dir)
	{
		if (ft_strncmp(dir->d_name, ".", 2) && ft_strncmp(dir->d_name, "..", 3))
			break ;
		dir = readdir(d);
	}
	while (dir)
	{
		len = ft_strlen(dir->d_name);
		if (!check_file(s, dir->d_name, len))
		{
			if (process_file(s->str, dir->d_name, buffer, s->head_type))
				return (errmsg_errno(19), 1);
			if (s->head_type)
				*len_ptr += ft_strlen(&s->str[s->start]) + 1;
			*len_ptr += len + 1;
		}
		dir = readdir(d);
	}
	*len_ptr -= 1;
	return (0);
}
