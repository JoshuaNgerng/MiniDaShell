/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:17:32 by jngerng           #+#    #+#             */
/*   Updated: 2023/12/04 21:19:58 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_file(t_shell *s, t_token *t)
{
	int		len;
	t_token	*list;
	char	*out;

	list = NULL;
	len = 0;
	if (search_expand(t->token, s->env, &list, &len))
		return (handle_error(s, 137), 1);
	out = (char *) malloc((len + 1) * sizeof(char));
	if (!out)
		return (1);
	if (copy_expand(out, t->token, list, 1))
		return (free_tokens(list), handle_error(s, 1), 1);
	free(t->token);
	t->token = out;
	free_tokens(list);
	return (0);
}

int	expand_here_doc(t_shell *s, t_token *t)
{
	int		i;
	int		j;
	int		len;
	char	*out;

	i = -1;
	len = 0;
	while (t->token[++ i])
		if (t->token[i] == '\'' || t->token[i] == '"')
			len ++;
	len = i - len;
	out = (char *) malloc((len + 1) * sizeof(char));
	if (!out)
		return (handle_error(s, 137), 1);
	i = -1;
	j = 0;
	while (t->token[++ i])
		if (t->token[i] != '\'' || t->token[i] != '"')
			out[j ++] = t->token[i];
	out[j] = '\0';
	free(t->token);
	t->token = out;
	return (0);
}

int	loop_files(t_shell *s, t_token *t)
{
	t_token	*ptr;

	ptr = t;
	while (ptr)
	{
		if (expand_file(s, ptr))
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

int	loop_cmd(t_shell *s, t_token *t)
{
	t_token	*prev;
	t_token	*now;
	t_token	*next;

	now = t;
	next = now->next;
	prev = NULL;
	while (next)
	{
		if (expand_cmd(now, &prev, s))
			return (1);
		now = next;
		next = next->next;
	}
	if (expand_cmd(now, &prev, s))
		return (1);
	return (0);
}

int	expand(t_shell *s, t_sect *sect)
{
	t_proc	*ptr;

	ptr = sect->block;
	while (ptr)
	{
		if (ptr->cmd)
		{
			if (loop_cmd(s, ptr->cmd))
				return (1);
		}
		if (ptr->f_read)
		{
			if (loop_files(s, ptr->f_read))
				return (1);
		}
		if (ptr->f_out)
		{
			if (loop_files(s, ptr->f_out))
				return (1);
		}
		ptr = ptr->next;
	}
	return (0);
}
