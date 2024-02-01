/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 09:59:47 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/01 10:22:12 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
helper function
update value of c and set type to 0 if quo is found
*/
static void	complete_quo_helper(t_token *new, char *r, int *c)
{
	int	i;

	new->token = r;
	new->type = *c;
	i = int_strchr(r, *c);
	if (i < 0)
		return ;
	*c = check_input(r, i + 1);
	new->type = 0;
}

/*
use for incomplete quotation
call readline and allocate next node of the link list
then check input then update c
type would be updated if quo is found
*/
static int	complete_quo(t_shell *s, t_token **tail, int *c)
{
	char	*r;
	t_token	*new;

	r = readline(">> ");
	if (!r)
	{
		if (!s->status)
			return (handle_error(s, 2), errmsg_token(*c), 1);
		return (1);
	}
	new = (t_token *) malloc (sizeof(t_token));
	(*tail)->next = new;
	if (!new)
		return (handle_error(s, 137), errmsg_errno(2), 1);
	(*tail) = (*tail)->next;
	(*tail)->next = NULL;
	complete_quo_helper(new, r, c);
	return (0);
}

/*
use for incomplete operators outside of quotation
call readline and allocate next node of the link list
then check input then update c
*/
static int	complete_sp(t_shell *s, t_token **tail, int *c)
{
	char	*r;
	t_token	*new;

	r = get_input(s, ">> ");
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

/*
do different checks for incomplete (') (") or OPERATORS
then update the incomplete symbol via the ptr to c
*/
int	complete_input_helper(t_shell *s, t_token **tail, int *c)
{
	if (*c == '\'' || *c == '"')
	{
		if (complete_quo(s, tail, c))
			return (1);
	}
	else if (*c & OPERATORS)
	{
		if (complete_sp(s, tail, c))
			return (1);
	}
	else if (*c > 0 && *c != '\'' && *c != '"' && *c & FILES)
		return (errmsg_var(1, "newline", 7), 1);
	return (0);
}

/*
r -> the inital readline
c -> represent the incomplete symbol

if an incomplete symbol occurs from initial readline
this function would call more readline till there is no incomplete symbol
intialize link list to hold memory for input
token hold the readline
type hold whether it is start or end of a quotation
*/
int	complete_input(t_shell *s, t_token **head, char *r, int *c)
{
	t_token	*tail;

	(*head) = (t_token *) malloc (sizeof(t_token));
	if (!(*head))
		return (free(r), 1);
	(*head)->token = r;
	tail = (*head);
	tail->type = 0;
	tail->next = NULL;
	if (*c == '\'' || *c == '"')
		tail->type = *c;
	while (*c > 0 && *c != end_b)
	{
		if (complete_input_helper(s, &tail, c))
			return (0);
	}
	return (0);
}
