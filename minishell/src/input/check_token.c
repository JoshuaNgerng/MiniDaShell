/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 09:16:25 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/07 15:58:18 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_logical_operator(char *input, int *index)
{
	int		i;
	char	out;

	i = *index;
	out = 0;
	if (input[i] == '|' && input[i + 1] == '|')
		out = _or;
	else if (input[i] == '&' && input[i + 1] == '&')
		out = _and;
	else if (input[i] == '|')
		out = _pipe;
	else if (input[i] == '&' && input[i + 1] != '&')
		errmsg_var(1, "&", 1);
	*index = i + 1;
	if (out == _and || out == _or)
		(*index)++;
	return (out);
}

int	check_redirection(char *input, int *index)
{
	int		i;
	char	out;

	i = *index;
	out = 0;
	if (input[i] == '>' && input[i + 1] == '>')
		out = _append;
	else if (input[i] == '<' && input[i + 1] == '<')
		out = here_doc;
	else if (input[i] == '<' && input[i + 1] == '>')
		out = _read | _write;
	else if (input[i] == '>')
		out = _write;
	else if (input[i] == '<')
		out = _read;
	*index = i + 1;
	if (!(out == _write || out == _read))
		*index = i + 2;
	return (out);
}

static void	update_ptr(int *new, int ref)
{
	if (new)
		*new = ref;
}

int	iter_token(char *input, int i, int *new)
{
	int	ref;

	ref = 0;
	while (input[i] && !ft_checkset(input[i], "&|<> ()"))
	{
		if (!ft_isascii(input[i]))
			return (errmsg(1), -1);
		if (input[i] == '"' || input[i] == '\'')
		{
			ref = input[i ++];
			while (input[i] && input[i] != ref)
				i ++;
			if (input[i] == ref)
				ref = 0;
			else
				return (update_ptr(new, ref), i);
		}
		i ++;
	}
	return (update_ptr(new, ref), i);
}
