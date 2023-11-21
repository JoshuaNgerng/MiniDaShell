/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 05:25:04 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/21 09:57:13 by jngerng          ###   ########.fr       */
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
	if (out == _append || out == here_doc)
		*index = i + 2;
	return (out);
}

int	iter_token(char *input, int i, int *new)
{
	while (input[i] && !ft_checkset(input[i], "&|<> "))
	{
		if (!ft_isascii(input[i]))
			return (errmsg(1), -1);
		if (input[i] == '"' || input[i] == '\'')
		{
			*new = input[i];
			while (input[i] && input[i] != *new)
				i ++;
			if (input[i] == *new)
				*new = 0;
			else
				return (i);
		}
		i ++;
	}
	return (i);
}
