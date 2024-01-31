/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_root.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:22:48 by jngerng           #+#    #+#             */
/*   Updated: 2024/01/31 15:21:18 by jngerng          ###   ########.fr       */
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
			return (errmsg_expand(t->token, e.list, e.list_malloc), free_tokens_empty(e.list),
				free_tokens(e.list_malloc), free(out), 1);
		else if (out[i] == -32)
			out[i] = ' ';
	}
	free(t->token);
	t->token = out;
	return (free_tokens_empty(e.list), free_tokens(e.list_malloc), 0);
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
	{
		if (t->token[i] != '\'' || t->token[i] != '"')
			out[j ++] = t->token[i];
	}
	out[j] = '\0';
	free(t->token);
	t->token = out;
	return (0);
}

static int	loop_files(t_shell *s, t_token *t, char *status)
{
	t_token	*ptr;

	// printf("test t_token files before\n");
	// dev_print_tokens(t);
	ptr = t;
	while (ptr)
	{
		if (expand_file(s, ptr, status))
			return (1);
		ptr = ptr->next;
	}
	// printf("test t_token files after\n");
	// dev_print_tokens(t);
	return (0);
}

static int	loop_cmd(t_shell *s, t_token *t, char *status)
{
	t_token	*prev;
	t_token	*now;
	t_token	*next;

	// printf("test t_token cmd before\n");
	// dev_print_tokens(t);
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
	// printf("test t_token cmd after\n");
	// dev_print_tokens(t);
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
	// printf("test before expand\n");
	// dev_print_sect(sect);
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
	// printf("test after expand\n");
	// dev_print_sect(sect);
	return (free(status), 0);
}
