/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:23:21 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/01 08:03:58 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*clean_token(char *str)
{
	int	i;

	i = -1;
	while (str[++ i])
	{
		if (str[i] == -32)
			str[i] = 32;
	}
	return (str);
}

int	empty_cmd(t_ptr *buffer, t_token *next)
{
	free(buffer->tail->token);
	buffer->tail->token = ft_strdup("");
	if (!buffer->tail->token)
		return (1);
	buffer->tail->next = next;
	return (0);
}

int	loop_strs_transfer(char **strs, t_ptr *buffer, t_token *next)
{
	int		i;
	t_token	*new;

	i = 0;
	while (strs[++ i])
	{
		new = (t_token *) malloc(sizeof(t_token));
		buffer->tail->next = new;
		if (!new)
		{
			buffer->tail->next = next;
			return (1);
		}
		new->token = clean_token(strs[i]);
		strs[i] = NULL;
		buffer->tail = buffer->tail->next;
	}
	buffer->tail->next = next;
	return (0);
}

int	expand_env_cmd(char *str, t_ptr *buffer, t_token *next)
{
	int		out;
	char	**strs;

	strs = ft_split(str, ' ');
	if (!strs)
		return (free(str), 1);
	free(str);
	if (!strs[0])
		return (free(strs), empty_cmd(buffer, next));
	free(buffer->tail->token);
	buffer->tail->token = clean_token(strs[0]);
	out = loop_strs_transfer(strs, buffer, next);
	return (free(strs), out);
}

/*
iter through the str in token and find $
then make list point to the env
get the space needed for allocation
then copy over from list (env)
free the list
then ft_split to get the different parts of line
a new list is made and inserted into the existing list
*/
int	expand_cmd(t_token *now, t_token **prev, t_shell *s, char *status)
{
	char		*line;
	t_token		*next;
	t_ptr		buffer;
	t_expand	e;

	next = now->next;
	buffer = (t_ptr){now, now};
	e = (t_expand){-1, 0, now->token, status, s, NULL, NULL};
	if (search_expand(s, &e))
		return (handle_error(s, 137), 1);
	line = (char *) malloc((e.len + 1) * sizeof(char));
	if (!line)
		return (free_tokens_empty(e.list),
			free_tokens(e.list_malloc), handle_error(s, 137), 1);
	copy_expand(line, now->token, e.list, e.list_malloc);
	free_tokens_empty(e.list);
	free_tokens(e.list_malloc);
	if (expand_env_cmd(line, &buffer, next))
		return (handle_error(s, 137), 1);
	if (!(*prev))
		return (0);
	(*prev)->next = buffer.head;
	*prev = buffer.tail;
	return (0);
}
