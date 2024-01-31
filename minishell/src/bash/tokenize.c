/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:30:43 by jngerng           #+#    #+#             */
/*   Updated: 2024/01/31 23:48:52 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_bracket(char *input, int i)
{
	int	brac;
	int	j;

	brac = 0;
	j = i;
	while (input[j])
	{
		if (input[j] == '(')
			brac ++;
		else if (input[j] == ')')
			brac --;
		j ++;
		if (brac == 0)
			break ;
	}
	return (j);
}

static t_token	*get_token(char *input, int i, int *index, int *type)
{
	int		j;
	t_token	*out;

	out = (t_token *) malloc (sizeof(t_token));
	if (!out)
		return (NULL);
	if (input[i] == '(')
		j = get_bracket(input, i);
	else if (input[i] == '$' && input[i + 1] == '(')
		j = get_bracket(input, i + 1);
	else
		j = iter_token(input, i, NULL);
	out->type = *type;
	out->token = ft_substr(input, i, j - i);
	if (!out->token)
		return (free(out), NULL);
	*index = j;
	return (out);
}

static int	get_token_input_helper(char *input, int *i, int *index, int *type)
{
	if (input[*i] == '|' || input[*i] == '&')
	{
		*type = check_logical_operator(input, i);
		*index = *i;
		return (1);
	}
	if (input[*i] == '(')
		*type = start_b;
	else if (input[*i] == '<' || input[*i] == '>')
	{
		*type = check_redirection(input, i);
		*i = pass_space(input, *i);
	}
	return (0);
}

static int	get_token_input(t_token **tail, char *input, int *index, int *type)
{
	int		i;
	t_token	*new;

	i = *index;
	i = pass_space(input, i);
	if (!input[i])
	{
		*index = i;
		return (0);
	}
	if (get_token_input_helper(input, &i, index, type))
		return (0);
	new = get_token(input, i, index, type);
	if (!(*tail))
	{
		*tail = new;
		(*tail)->next = NULL;
		return (0);
	}
	(*tail)->next = new;
	if (!new)
		return (1);
	*tail = (*tail)->next;
	(*tail)->next = NULL;
	return (0);
}

int	tokenize_input(t_shell *s, t_token **head, int *index, int *type)
{
	t_token	*tail;

	*type = 0;
	*head = NULL;
	if (get_token_input(head, s->input, index, type))
		return (errmsg_errno(4), handle_error(s, 137), 1);
	tail = *head;
	while (s->input[*index] && !(*type & OPERATORS))
	{
		*type = 0;
		if (get_token_input(&tail, s->input, index, type))
			return (free_tokens(*head), errmsg_errno(4),
				handle_error(s, 137), 1);
	}
	return (0);
}
