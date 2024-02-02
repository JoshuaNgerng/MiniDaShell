/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_root.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:22:48 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/02 10:40:47 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_file(t_shell *s, t_token *t, char *status)
{
	int			i;
	t_expand	e;
	char		*out;

	e = (t_expand){-1, 0, t->token, status, s, NULL, NULL};
	if (search_expand(s, &e))
		return (handle_error(s, 137), 1);
	out = (char *) malloc((e.len + 1) * sizeof(char));
	if (!out)
		return (handle_error(s, 137), free_tokens_empty(e.list), 1);
	copy_expand(out, t->token, e.list, e.list_malloc);
	i = -1;
	while (out[++ i])
	{
		if (out[i] == ' ')
			return (errmsg_expand(t->token, e.list, e.list_malloc),
				free_tokens_empty(e.list), free_tokens(e.list_malloc),
				free(out), 1);
		else if (out[i] == -32)
			out[i] = ' ';
	}
	free(t->token);
	t->token = out;
	return (free_tokens_empty(e.list), free_tokens(e.list_malloc), 0);
}

static int	loop_files(t_shell *s, t_token *t, char *status)
{
	t_token	*ptr;

	ptr = t;
	while (ptr)
	{
		if (expand_file(s, ptr, status))
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

static int	loop_cmd(t_shell *s, t_token *t, char *status)
{
	t_token	*prev;
	t_token	*now;
	t_token	*next;

	if (!t)
		return (0);
	now = t;
	next = now->next;
	prev = NULL;
	while (next)
	{
		if (expand_cmd(now, &prev, s, status))
			return (1);
		now = next;
		next = next->next;
	}
	if (expand_cmd(now, &prev, s, status))
		return (1);
	return (0);
}

int	expand(t_shell *s, t_sect *sect)
{
	t_proc	*ptr;
	char	*status;

	ptr = sect->block;
	status = ft_itoa(s->status);
	if (!status)
		return (errmsg_errno(15), handle_error(s, 137), 1);
	while (ptr)
	{
		if (loop_cmd(s, ptr->cmd, status))
			return (free(status), 1);
		if (loop_files(s, ptr->f_read, status))
			return (free(status), 1);
		if (loop_files(s, ptr->f_out, status))
			return (free(status), 1);
		ptr = ptr->next;
	}
	return (free(status), 0);
}
