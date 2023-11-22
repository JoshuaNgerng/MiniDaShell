/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 02:33:32 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/14 02:33:36 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	int_strchr(char *str, char c)
// {
// 	int	i;

// 	i = -1;
// 	while (str[++i])
// 		if (str[i] == c)
// 			return (i);
// 	return (-1);
// }

static int	complete_quo(t_shell *s, t_token **tail, int *c)
{
	int		i;
	char	*r;
	t_token	*new;

	r = readline(">> ");
	if (!r)
	{
		if (errno)
			return (handle_error(s, 137), errmsg_errno(2), 1);
		return (handle_error(s, 2), errmsg_token(*c), 1);
	}
	new = (t_token *) malloc (sizeof(t_token));
	(*tail)->next = new;
	if (!new)
		return (handle_error(s, 137), errmsg_errno(2), 1);
	new->token = r;
	(*tail) = (*tail)->next;
	(*tail)->next = NULL;
	new->type = *c;
	i = int_strchr(r, *c);
	if (i >= 0)
	{
		*c = check_input(r, i);
		new->type = 0;
	}
	return (0);
}

static int	complete_sp(t_shell *s, t_token **tail, int *c)
{
	char	*r;
	t_token	*new;

	r = get_input(s, ">>");
	if (!r)
	{
		if (!s->status)
			return (handle_error(s, 2), errmsg(2), 1);
		return (1);
	}
	new = (t_token *) malloc (sizeof(t_token));
	(*tail)->next = new;
	if (!new)
		return (handle_error(s, 137), errmsg_errno(2), 1);
	new->token = r;
	new->next = NULL;
	(*tail) = (*tail)->next;
	(*tail)->next = NULL;
	*c = check_input(r, 0);
	new->type = 0;
	return (0);
}

int	complete_input(t_shell *s, t_token **head, char *r, int c)
{
	t_token *tail;

	(*head) = (t_token *) malloc (sizeof(t_token));
	if (!(*head))
		return (free(r), 1);
	(*head)->token = r;
	tail = (*head);
	tail->type = 0;
	tail->next = NULL;
	if (c == '\'' || c == '"')
		tail->type = c;
	while (c > 0 && c != end_b)
	{
		if (c == '\'' || c == '"')
		{
			if (complete_quo(s, &tail, &c))
				return (1);
		}
		else if (c & OPERATORS)
		{
			if (complete_sp(s, &tail, &c))
				return (1);
		}
		else if (c > 0 && c & FILES)
			return (1);
	}
	return (0);
}
