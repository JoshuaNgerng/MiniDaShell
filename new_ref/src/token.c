/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:11:00 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/22 00:33:02 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_token(char *input, int i, int *index, int *type)
{
	int		j;
	t_token	*out;

	out = (t_token *) malloc (sizeof(t_token));
	if (!out)
		return (NULL);
	if (input[i] == '(')
	{
		*type = start_b;
		j = i + 1;
	}
	else if (input[i] == ')')
	{
		*type = end_b;
		j = i + 1;
	}
	else
		j = iter_token(input, i, NULL);
	out->type = *type;
	out->token = ft_substr(input, i, j - i);
	if (!out->token)
		return (free(out), NULL);
	*index = j;
	return (out);
}

int	get_token_input_helper(char *input, int i, int *index, int *type)
{
	if (input[i] == '|' || input[i] == '&')
	{
		*type = check_logical_operator(input, &i);
		*index = i;
		return (1);
	}
	else if (input[i] == '<' || input[i] == '>')
	{
		*type = check_redirection(input, &i);
		i = pass_space(input, i);
	}
	return (0);
}

int	get_token_input(t_token **tail, char *input, int *index, int *type)
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
	if (get_token_input_helper(input, i, index, type))
		return (0);
	new = get_token(input, i, index, type);
	(*tail)->next = new;
	if (!new)
		return (1);
	*tail = (*tail)->next;
	(*tail)->next = NULL;
	return (0);
}

t_token	*tokenize_input(t_shell *s, int *index, int *type)
{
	t_token *head;
	t_token	*tail;

	*type = 0;
	head = NULL;
	if (get_token_input(&head, s->input, index, type))
		return (errmsg_errno(4), handle_error(s, 137), NULL);
	tail = head;
	while (s->input[*index] && *type & LOGIC)
	{
		*type = 0;
		if (get_token_input(&tail, s->input, index, &type))
			return (free_tokens(head), errmsg_errno(4), \
					handle_error(s, 137), NULL);
	}
	return (head);
}
