/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 02:40:05 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/14 02:40:36 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_new_token(char *input, int i, int *new, int *brac)
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
	else
		i = iter_token(input, i, new);
	return (i);
}

static int	check_inside_loop(char *input, int i, int *prev, int *brac)
{
	int	j;
	int	new;

	new = 0;
	i = pass_space(input, i);
	if (!input[i])
		return (i);
	j = get_new_token(input, i, &new, brac);
	if (j < 0)
		return (-1);
	if (*prev & FILES && new)
		return (errmsg_token(new), -1);
	else if (!new && *prev == start_b)
		return (errmsg_var(1, &input[i], j - i), -1);
	else if (new == _pipe && (*prev > 0 && *prev < end_b))
		return (errmsg_token(new), -1);
	else if (new & LOGIC && *prev && *prev != end_b)
		return (errmsg_token(new), -1);
	else if (new & start_b && !(*prev & (OPERATORS | start_b)))
		return (errmsg_token(new), -1);
	else if (new & end_b && (*prev && *prev != end_b))
		return (errmsg_token(new), -1);
	*prev = new;
	return (j);
}

int	check_input(char *input, int i)
{
	int	out;
	int	brac;

	if (!input)
		return (0);
	out = 0;
	brac = 0;
	if (!i)
	{
		i = pass_space(input, i);
		if (ft_checkset(input[i], "|&)"))
			return (-1);
		if (input[i] == '(')
		{
			i ++;
			out = start_b;
			brac = 1;
		}
		else if (input[i] == '<' || input[i] == '>')
			out = check_redirection(input, &i);
		else
			i = iter_token(input, i, &out);
	}
	while (i >= 0 && input[i])
		i = check_inside_loop(input, i, &out, &brac);
	if (brac > 0)
		return (-1);
	if (i < 0)
		return (-1);
	return (out);
}
