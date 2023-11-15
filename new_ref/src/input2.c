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

int	check_iter_token(char *input, int i, t_check *check)
{
	if (!check->token || check->token == 'e')
		return (-1);
	while (input[i] && !ft_checkset(input[i], "&|<> "))
	{
		if (!ft_isascii(input[i]))
			return (errmsg(1), -1);
		if (input[i] == '"' || input[i] == '\'')
		{
			check->quo = input[i];
			while (input[i] && input[i] != check->quo)
				i ++;
			if (input[i] == check->quo)
				check->quo = 0;
			else
				return (i);
		}
		i ++;
	}
	check->token = 'c';
	return (i);
}

int	check_brackets(char c, int *i, t_check *check)
{
	if (c == '(')
	{
		if (!ft_check(check->token, "son"))
			return (1);
		check->token = 's';
		check->brac ++;
		(*i)++;
	}
	else if (c == ')')
	{
		if (check->token != 'c' && check->token != 'e')
			return (1);
		check->token = 'e';
		check->brac --;
		(*i)++;
	}
	return (0);
}

int	check_meta_char(char *input, int *start, t_check *check)
{
	int		i;
	char	prev;

	i = *start;
	prev = check->token;
	if (input[i] == '>' || input[i] == '<')
	{
		check->token = check_redirection(input, start);
		return (0);
	}
	check->token = check_logical_operator(input, &i);
	if (!check->token)
		return (1);
	if (check->token == 'p')
	{
		if (prev != 'c')
			return (1);
	}
	else if (check->token == 'n')
	{
		;
	}
	else if (check->token == 'o')
	{
		;
	}
	*start = i;
	return (0);
}

int	check_inside_loop(char *input, int i, t_check *check)
{
	i = pass_space(input, i);
	if (ft_checkset(input[i], "&|<>()"))
	{
		if (ft_checkset(check->token, "hrwa"))
			return (-1);
		if (check_brackets_quo(input[i], &i, check))
			return (-1);
		if (input[i] <= ')')
			return (i);
		if (check_meta_char(input, &i, check))
			return (-1);
	}
	else
		i = check_iter_token(input, i, check);
	return (i);
}

char	check_input(char *input, int i)
{
	t_check	check;

	check = (t_check){0, 'c', 0};
	if (!i)
	{
		i = pass_space(input, i);
		if (ft_checkset(input[i], "|&)"))
			return (-1);
		if (input[i] == '(')
			check.brac = 1;
		else if (input[i] == '<' || input[i] == '>')
			check.token = check_redirection(input, &i);
	}
	while (input[i])
	{
		i = check_inside_loop(input[i], i, &check);
		if (i < 0 || check.brac < 0 || !check.token)
			return (-1);
	}
	if (brac)
		return (-1);
	if (check.quo)
		return (check.quo)
	return (check.token);
}
