/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_star.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 08:58:36 by jngerng           #+#    #+#             */
/*   Updated: 2024/01/31 15:03:57 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	none_star(t_token *new, t_expand *e)
{
	free(new);
	e->len ++;
}

int	iter_str_check(t_star *s, int *ptr)
{
	while (s->start > -1 && s->str[s->start] != ' ')
	{
		if (ft_checkset(s->str[s->start], "'\"\\:*?<>|"))
			return (1);
		if (s->str[s->start] == '/')
			*ptr = 1;
		s->start --;
	}
	s->start ++;
	return (0);
}

int	iter_str(t_star *s)
{
	while (s->str[s->end] && s->str[s->end] != ' ')
	{
		if (ft_checkset(s->str[s->end], "'\"\\/:*?<>|"))
			return (1);
		s->end ++;
	}
	s->end --;
	return (0);
}

int	expand_star(t_token *new, t_ptr *buffer, t_expand *e)
{
	int		check;
	int		len;
	t_star	star;

	check = 0;
	len = 0;
	// printf("test star\n");
	star = (t_star){e->i, e->i - 1, 0, e->i + 1, e->str};
	// printf("test star\n");
	if (iter_str_check(&star, &check))
		return (none_star(new, e), 0);
	// printf("test star\n");
	if (check == 1 && e->str[star.star_pos - 1] != '/')
		return (none_star(new, e), 0);
	star.head_type = check;
	if (iter_str(&star))
		return (none_star(new, e), 0);
	// printf("testing\n%s\n%s\nend\n", &e->str[star.start], &e->str[star.star_pos]);
	if (read_star(&star, new, &len))
		return (none_star(new, e), 1);
	if (!new->token)
		return (none_star(new, e), 0);
	e->len -= star.start - star.star_pos;
	e->str[star.start] *= -1;
	new->type = star.end - star.start;
	// printf("testing type(skip)%d\n", new->type);
	e->i = star.end;
	e->len += len;
	return (transfer_token_ptr(buffer, new), 0);
}
