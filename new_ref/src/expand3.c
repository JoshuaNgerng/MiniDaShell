/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 10:54:49 by jngerng           #+#    #+#             */
/*   Updated: 2023/12/04 20:23:53 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_length(char *str, int index)
{
	int	len;
	int	quo;

	len = 0;
	quo = 0;
	while (str[index])
	{
		if (str[index] == ' ' && !quo)
			return (len);
		if (str[index] == '\'' || str[index] == '"')
		{
			quo = read_quo(str[index], quo);
			if (quo && quo != str[index])
				len ++;
		}
		else
			len ++;
		index ++;
	}
	return (len);
}


int	clean_token(t_token *t, char *str, int *index)
{
	int		i;
	int		j;
	int		quo;
	int		len;
	char	*new_str;

	len = get_length(str, *index);
	new_str = (char *) malloc((len + 1) * sizeof(char));
	if (!new_str)
		return (1);
	i = -1;
	quo = 0;
	j = *index;
	while (++ i < len)
	{
		if (str[j] == '\'' || str[j] == '"')
		{
			quo = read_quo(str[j], quo);
			if (quo && quo != str[j])
				new_str[i] = str[j];
		}
		else
			new_str[i] = str[j];
		j ++;
	}
	new_str[i] = '\0';
	if (t->token)
		free(t->token);
	*index = j;
	t->token = new_str;
	return (0);
}

int	expand_env_cmd(char *str, t_ptr *buffer, t_token *next)
{
	int		i;
	t_token	*new;

	i = 0;
	if (clean_token(buffer->head, str, &i))
		return (1);
	i = pass_space(str, i);
	while (str[i])
	{
		new = (t_token *) malloc(sizeof(t_token));
		buffer->tail->next = new;
		if (!new)
		{
			buffer->tail->next = next;
			return (1);
		}
		new->token = NULL;
		buffer->tail = buffer->tail->next;
		if (clean_token(buffer->tail, str, &i))
			return (1);
		i = pass_space(str, i);
	}
	buffer->tail->next = next;
	return (0);
}

int	expand_cmd(t_token *now, t_token **prev, t_shell *s)//, int *size)
{
	int		len;
	char	*line;
	t_token	*next;
	t_token	*list;
	t_ptr	buffer;

	len = 0;
	next = now->next;
	buffer = (t_ptr){now, now};
	list = NULL;
	if (search_expand(now->token, s->env, &list, &len))
		return (handle_error(s, 137), 1);
	line = (char *) malloc((len + 1) * sizeof(char));
	if (!line)
		return (free_tokens_empty(list), handle_error(s, 137), 1);
	copy_expand(line, now->token, list, 0);
	free_tokens_empty(list);
	if (expand_env_cmd(line, &buffer, next))
		return (free(line), handle_error(s, 137), 1);
	if (!*prev)
		return (free(line), 0);
	(*prev)->next = buffer.head;
	*prev = buffer.tail;
	free(line);
	return (0);
}
