/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 09:59:45 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/02 16:13:39 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_new_token(char *input, int i, int *new, int *brac)
{
	if (input[i] == '>' || input[i] == '<')
		*new = check_redirection(input, &i);
	else if (input[i] == '|' || input[i] == '&')
	{
		*new = check_logical_operator(input, &i);
		if (!(*new))
			return (-1);
	}
	else if (input[i] == '(')
	{
		*new = start_b;
		(*brac)++;
		i ++;
	}
	else if (input[i] == ')')
	{
		*new = end_b;
		(*brac)--;
		i ++;
	}
	else if (input[i] == '$' && input[i + 1] == '(')
		i = get_bracket(input, i + 1);
	else
		i = iter_token(input, i, new);
	return (i);
}

static int	start_check_input(char *input, int *ptr, int *out, int *brac)
{
	int	i;

	i = *ptr;
	i = pass_space(input, i);
	if (ft_checkset(input[i], "|&)"))
	{
		get_new_token(input, i, out, brac);
		return (errmsg_token(*out), -1);
	}
	if (input[i] == '(')
	{
		i ++;
		*out = start_b;
		*brac = 1;
	}
	else if (input[i] == '<' || input[i] == '>')
		*out = check_redirection(input, &i);
	else
		i = iter_token(input, i, out);
	*ptr = i;
	return (0);
}

/*
check input used on each readline
compare next token with the prev one
loop input till unexpected token is found
return error with found and nothing on success or incomplete tokens 
*/
int	check_input(char *input, int i)
{
	int	out;
	int	brac;

	if (!input)
		return (0);
	out = 0;
	brac = 0;
	if (!i)
		if (start_check_input(input, &i, &out, &brac))
			return (-1);
	while (i >= 0 && input[i])
		i = check_inside_loop(input, i, &out, &brac);
	if (i < 0)
		return (-1);
	if (brac > 0)
		return (errmsg_var(1, ")", 1), -1);
	return (out);
}
