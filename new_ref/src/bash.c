/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:30:13 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/28 08:19:52 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_end_brac(char *input, int i)
{
	int	brac;

	brac = 1;
	while (input[i] && brac)
	{
		if (input[i] == '(')
			brac ++;
		else if (input[i] == ')')
			brac --;
		i ++;
	}
	return (i);
}

int	subshell(t_shell *s, int *index)
{
	int	i;
	int	end;
	int	pid;

	pid = fork();
	if (pid < 0)
		return (errmsg_errno(), handle_error(s, 137), -1);
	end = get_end_brac(s->input, *index);
	if (!pid)
	{
		;
	}
	else
	{
		;
	}
	return (0);
}

// loop brackets with subshell
// need to rewrite token buffer
// check type for brackets
// open subshell
// if its logical operator or end
// do_proc in main
// skip skip till end brack or skip not needed proc
int	bash(t_shell *s)
{
	int	i;
	int	type;

	i = 0;
	type = 0;
	while (s->input[i])
	{
		if (process_init(s, &i, &type))
			return (1);
		if (type == start_b)
		{
			if (subshell(s, &i))
				return (1);
		}
		else
		{
			if (do_processes(s))
				return (1);
		}
		i = check_next_proc(s, s->input, i, type);
	}
	return (0);
}
