/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:40:34 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/02 16:15:05 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_special_status(t_token *new, t_ptr *buffer, t_expand *e)
{
	new->token = e->status;
	new->type = 1;
	e->len += ft_strlen(e->status);
	transfer_token_ptr(buffer, new);
	e->i ++;
	return (0);
}

static char	*handle_env_search(t_env *search, t_expand *e)
{
	if (!search)
		return (NULL);
	e->len += ft_strlen(search->value);
	return (search->value);
}

static int	expand_env_list(t_expand *e, t_ptr *buffer, t_ptr *buffer_malloc)
{
	int		i;
	t_env	*search;
	t_token	*new;

	i = e->i + 1;
	new = (t_token *) malloc(sizeof(t_token));
	if (!new)
		return (errmsg_errno(17), -1);
	if (e->str[e->i] == '*')
		return (expand_star(new, buffer_malloc, e));
	if (e->str[i] == '?')
		return (expand_special_status(new, buffer, e));
	while (e->str[i] && !ft_checkset(e->str[i], "*$ \\\"'"))
		i ++;
	search = search_env(e->s->env, &e->str[e->i + 1], i - e->i - 1);
	new->token = handle_env_search(search, e);
	new->type = i - 1 - e->i;
	e->i = i - 1;
	return (transfer_token_ptr(buffer, new), 0);
}

static int	check_str_expand(char *str, int i, int *len, int *quo)
{
	if (str[i] == '\'' || str[i] == '"')
	{
		*quo = read_quo(str[i], *quo);
		if (*quo && *quo != str[i])
			(*len)++;
		return (0);
	}
	if (str[i] == '$' && str[i + 1] && !ft_checkset(str[i + 1], "'\" "))
	{
		if (!(*quo) || *quo == '"')
			return (1);
	}
	if (str[i] == '*' && !(*quo))
		return (1);
	(*len)++;
	return (0);
}

int	search_expand(t_shell *s, t_expand *e)
{
	int		quo;
	t_ptr	buffer;
	t_ptr	buffer_malloc;

	quo = 0;
	buffer = (t_ptr){0, 0};
	buffer_malloc = (t_ptr){0, 0};
	while (e->str[++ e->i])
	{
		if (check_str_expand(e->str, e->i, &e->len, &quo))
		{
			if (expand_env_list(e, &buffer, &buffer_malloc) < 0)
				return (handle_error(s, 137), free_tokens_empty(buffer.head),
					free_tokens(buffer_malloc.head), 1);
		}
	}
	e->list = buffer.head;
	e->list_malloc = buffer_malloc.head;
	return (0);
}
