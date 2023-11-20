/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 05:25:04 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/14 05:25:55 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	check_logical_operator(char *input, int *index)
{
	int		i;
	char	out;

	i = *index;
	out = 0;
	if (input[i] == '|' && input[i + 1] == '|')
		out = 'o';
	else if (input[i] == '&' && input[i + 1] == '&')
		out = 'n';
	else if (input[i] == '|')
		out = 'p';
	else if (input[i] == '&' && input[i + 1] != '&')
		errmsg_var(1, "&");
	*index = i + 1;
	if (out == 'o' || out == 'n')
		(*index)++;
	return (out);
}

char	check_redirection(char *input, int *index)
{
	int		i;
	char	out;

	i = *index;
	out = 0;
	if (input[i] == '>' && input[i + 1] == '>')
		out = 'a';
	else if (input[i] == '<' && input[i + 1] == '<')
		out = 'h';
	else if (input[i] == '<' && input[i + 1] == '>')
		out = 's';
	else if (input[i] == '>' && input[i + 1] == '<')
		return (out);
	else if (input[i] == '>')
		out = 'w';
	else if (input[i] == '<')
		out = 'r';
	if (out == 'r' || out == 'w')
		*index = i + 1;
	else if (out == 'a' || out == 'h')
		*index = i + 2;
	return (out);
}

int	iter_token()
{
	;
}