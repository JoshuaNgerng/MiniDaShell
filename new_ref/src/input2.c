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

/*
se on p hrwa

(
&
)
>
<
|


*/

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
	}
	else if (c == ')')
	{
		if (ft_check(check->token, "sponhrwa"))
			return (1);
		check->token = 'e';
		check->brac --;
	}
	(*i)++;
	return (0);
}
/*
int	check_inside_loop(char *input, int i, t_check *check)
{
	i = pass_space(input, i);
	if (check->token == "hrwa")
	if (input[i] == '>' || input[i] == '<')
	{
		if (check->token != 'c')
			return (-1);
		check->token = check_redirection(input, &i);
		else if (input[i] == '|' || input[i] == '&')
			check->token = check_logical_operator(input, &i);
	}
	else if (input[i] == '(' || input[i] == ')')
		if (check_brackets_quo(input[i], &i, check))
			return (-1);
	else
		i = check_iter_token(input, i, check);
	return (i);
}
*/

int	get_new_token(char *input, int i, char *new)
{
	i = pass_space(input, i);
	if (input[i] == '>' || input[i] == '<')
		new = check_redirection(input, &i);
	else if (input[i] == '|' || input[i] == '&')
	{
		new = check_logical_operator(input, &i);
		if (!new)
			return (errmsg_var(1, "&", 1), -1);
	}
	else if (input[i] == '(')
	{
		new = 's';
		i ++;
	}
	else if (input[i] == ')')
	{
		new = 'e';
		i ++;
	}
	return (i);
}

// check prev 
int	check_inside_loop(char *input, int i, t_check *check)
{
	int		j;
	char	new;

	new = 0;
	j = get_new_token(char *input, int i, &new);
	if (j < 0)
		return (-1);
	if (!input[j])
		return (j);
	if (!new.token)
		j = check_iter_token(input, j, check); // token preseve last
	if (check->token == 'hraw' && new.token != 'c')
		return (-1);
	if (new.token == 'c' && check->token == 's')
		return (-1);
	if (new.token == 's' && check->token != "on")
		return (-1);
	if (new.token == 'e' && check->token != 'c')
		return (-1);
	if (new.token == 'on' && check->token == 'ons')
		return (-1);
	if (new.token == 'p' && check->token == 'onp' || check->token == 'se')
		return (-1);
	//check_new_token (expected tokens)
	*check = new; 
	return (j);
}

char	check_input(char *input, int i)
{
	t_check	check;

	check = (t_check){0, 'c', 0};
	if (!input)
		return ('c');
	if (!i)
	{
		i = pass_space(input, i);
		if (ft_checkset(input[i], "|&)"))
			return (-1);
		if (input[i] == '(')
			check.brac = 1;
		else if (input[i] == '<' || input[i] == '>')
			check.token = check_redirection(input, &i);
		else
			i = check_iter_token(input, i, &check);
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
