/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:12:07 by jngerng           #+#    #+#             */
/*   Updated: 2023/12/04 21:17:43 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_quo(char ref, int quo)
{
	if (quo)
	{
		if (ref == quo)
			quo = 0;
	}
	else
		quo = ref;
	return (quo);
}

int	get_env_token(t_env *env, char *str, t_ptr *ptr, int *index, int *len)
{
	int		i;
	t_env	*search;
	t_token	*new;

	i = *index + 1;
	new = (t_token *) malloc(sizeof(t_token));
	if (!new)
		return (1);
	while (str[i] && !ft_checkset(str[i], "*$ \\\"'"))
		i ++;
	search = search_env(env, &str[(*index) + 1], i - 1);
	if (!search)
	{
		new->token = ft_strdup("");
		if (len)
			*len += ft_strlen(new->token);
	}
	else
	{
		new->token = search->value;
		if (len)
			*len += ft_strlen(new->token);
	}
	new->type = i - 1;
	transfer_token_ptr(ptr, new);
	*index = new->type;
	return (0);
}

int	search_expand(char *str, t_env *env, t_token **list, int *len)
{
	int		i;
	int		l;
	int		quo;
	t_ptr	buffer;

	i = -1;
	l = 0;
	quo = 0;
	buffer = (t_ptr){0, 0};
	while (str[++ i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quo = read_quo(str[i], quo);
			if (quo && quo != str[i])
				l ++;
		}
		else if (str[i] == '$' && (!quo || quo == '"'))
		{
			if (get_env_token(env, str, &buffer, &i, &l))
				return (free_tokens_empty(buffer.head), 1);
		}
		else
			l ++;
	}
	*list = buffer.head;
	*len = l;
	return (0);
}

static int	copy_expand_helper(char *dst, t_token *list, int *check, int quo)
{
	int	i;

	if (!list || !list->token)
		return (0);
	if (quo)
	{
		i = -1;
		while (list->token[++ i])
			dst[i] = list->token[i];
	}
	else
	{
		i = -1;
		while (list->token[++ i])
		{
			if (list->token[i] == ' ')
				*check = 1;
			dst[i] = list->token[i];
		}
	}
	return (i);
}

int	copy_expand(char *dst, char *src, t_token *list, int file)
{
	int	i;
	int	j;
	int	quo;
	int	check;

	i = -1;
	j = 0;
	quo = 0;
	check = 0;
	while (src[++ i])
	{
		if (src[i] == '\'' || src[i] == '"')
		{
			quo = read_quo(src[i], quo);
			if (quo && quo != src[i])
				dst[j ++] = src[i];
		}
		else if (src[i] == '$' && (!quo || quo == '"'))
		{
			j += copy_expand_helper(&dst[j], list, &check, quo);
			if (file && check == 1)
				return (errmsg_var(-1, &src[i + 1], list->type), 1);
			i += list->type;
			list = list->next;
		}
		else
			dst[j ++] = src[i];
	}
	dst[j] = '\0';
	return (0);
}
