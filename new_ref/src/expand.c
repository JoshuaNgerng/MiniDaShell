/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:17:32 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/29 19:42:25 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_file(t_shell *s, t_token *t)
{
	int		len;
	int		check;
	t_token	*list;
	char	*out;

	check = 0;
	list = NULL;
	if (search_expand(t->token, &list, &len, &check))
		return (1);
	if (check)
		return (errmsg(-1), 1);
	out = (char *) malloc((len + 1) * sizeof(char));
	if (!out)
		return (1);
	copy_expand(out, list, t->token);
	free(t->token);
	t->token = out;
	return (0);
}

int	expand_cmd(t_shell *s, t_token *t)
{
	int		len;
	t_token	*list;
	char	*out;

	list = NULL;
	if (search_expand(t->token, &list, &len, NULL))
		return (1);
	out = (char *) malloc((len + 1) * sizeof(char));
	if (!out)
		return (1);
	copy_expand(out, list, t->token);
	free(t->token);
	t->token = out;
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
		if (t->token[i] != '\'' || t->token[i] != '"')
			len ++;
	len = i - len;
	out = (char *) malloc((len + 1) * sizeof(char));
	if (!out)
		return (1);
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

int	loop_tokens(t_shell *s, t_token *t, int(*f)(t_shell *, t_token *))
{
	t_token	*ptr;

	ptr = t;
	while (ptr)
	{
		if (f(s, ptr))
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

int	expand(t_shell *s, t_buffer *b)
{
	if (b->cmd.head)
	{
		if (loop_tokens(s, b->cmd.head, &expand_cmd))
			return (1);
	}
	if (b->here_doc.head)
	{
		if (loop_tokens(s, b->here_doc.head, &expand_here_doc))
			return (1);
	}
	if (b->read.head)
	{
		if (loop_tokens(s, b->read.head, &expand_file))
			return (1);
	}
	if (b->out.head)
	{
		if (loop_tokens(s, b->out.head, &expand_file))
			return (1);
	}
	return (0);
}