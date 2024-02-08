/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 09:59:45 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/07 22:56:09 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_new_token(char *input, int i, int *out, t_check *c)
{
	if (input[i] == '>' || input[i] == '<')
		*out = check_redirection(input, &i);
	else if (input[i] == '|' || input[i] == '&')
	{
		*out = check_logical_operator(input, &i);
		if (!(*out))
			return (-1);
	}
	else if (input[i] == '(')
	{
		*out = start_b;
		c->brac ++;
		c->brac_state = 1;
		i ++;
	}
	else if (input[i] == ')')
	{
		*out = end_b;
		c->brac --;
		i ++;
	}
	else
		i = iter_token(input, i, out);
	return (i);
}

static int	start_check_input(char *input, int *ptr, int *out, t_check *c)
{
	int	i;

	i = *ptr;
	i = pass_space(input, i);
	if (ft_checkset(input[i], "|&)"))
	{
		get_new_token(input, i, out, c);
		return (errmsg_token(*out), -1);
	}
	if (input[i] == '(')
	{
		i ++;
		*out = start_b;
		c->brac = 1;
		c->brac_state = 1;
	}
	else if (input[i] == '<' || input[i] == '>')
		*out = check_redirection(input, &i);
	else
		i = iter_token(input, i, out);
	*ptr = i;
	return (0);
}

static int	check_inside_loop(char *input, int i, int *out, t_check *c)
{
	int	j;
	int	new;

	new = 0;
	i = pass_space(input, i);
	if (!input[i])
		return (i);
	j = get_new_token(input, i, &new, c);
	if (j < 0)
		return (-1);
	if (!new && c->brac_state && !(c->brac) && !(*out & FILES))
		return (errmsg_var(1, &input[i], j - i), -1);
	if (check_new_prev_tokens(new, *out))
		return (-1);
	if (new & OPERATORS && !(c->brac))
		c->brac_state = 0;
	*out = new;
	return (j);
}

/*
check input used on each readline
compare next token with the prev one
loop input till unexpected token is found
return error with found and nothing on success or incomplete tokens
*/
int	check_input(char *input, int i)
{
	int		out;
	t_check	c;

	if (!input)
		return (0);
	c = (t_check){0, 0};
	if (!i)
	{
		if (start_check_input(input, &i, &out, &c))
			return (-1);
	}
	while (i >= 0 && input[i])
		i = check_inside_loop(input, i, &out, &c);
	if (i < 0)
		return (-1);
	if (c.brac != 0)
		return (errmsg_var(1, ")", 1), -1);
	return (out);
}
