/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:11:00 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/22 13:13:08 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*get_token(char *input, int i, int *index, int *type)
{
	int		j;
	t_token	*out;

	out = (t_token *) malloc (sizeof(t_token));
	if (!out)
		return (NULL);
	j = iter_token(input, i, NULL);
	// printf("testing indexes i(%d) j(%d)\n", i, j);
	out->type = *type;
	out->token = ft_substr(input, i, j - i);
	if (!out->token)
		return (free(out), NULL);
	*index = j;
	// printf("test new token str: |%s| type |%d|\n", out->token, out->type);
	return (out);
}

static int	get_token_input_helper(char *input, int *i, int *index, int *type)
{
	if (input[*i] == '|' || input[*i] == '&')
	{
		*type = check_logical_operator(input, i);
		*index = *i;
	}
	else if (input[*i] == '(')
	{
		*type = start_b;
		*index = *i + 1;
	}
	else if (input[*i] == ')')
	{
		*type = end_b;
		*index = *i + 1;
	}
	else if (input[*i] == '<' || input[*i] == '>')
	{
		*type = check_redirection(input, i);
		*i = pass_space(input, *i);
		return (0);
	}
	return (1);
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
	// printf("outer testing index %d type %d\n", *index, *type);
	while (s->input[*index] && !(*type & OPERATORS))
	{
		*type = 0;
		if (get_token_input(&tail, s->input, index, type))
			return (free_tokens(head), errmsg_errno(4), \
					handle_error(s, 137), 1);
		// printf("inner testing index %d type %d\n", *index, *type);
	}
	// printf("test return tokens\n");
	// dev_print_tokens(head);
	return (0);
}
// ls > a
// 0123456