/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:30:13 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/28 10:46:41 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_end_brac(char *input, int i)
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
	int	status;
	int	end;
	int	pid;

	end = get_end_brac(s->input, *index);
	pid = fork();
	if (pid < 0)
		return (errmsg_errno(7), handle_error(s, 137), -1);
	if (!pid)
	{
		while (*index < end)
			if (do_bash(s, index))
				free_all_exit(s, 2);
		free_all_exit(s, 0);
	}
	else
	{
		status = 0;
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) || WIFEXITED(status))
			return (handle_error(2, WIFEXITED(status)), 1);
		s->status = WIFEXITED(status);
		*index = end;
	}
	return (0);
}

static int	check_next_proc(t_shell *s, int index, int type)
{
	int	skip;

	skip = 0;
	if (type == _or && !s->status)
		skip = type;
	else if (type == _and && s->status)
		skip = type;
	if (skip)
	{
		while (s->input[index])
		{
			if (s->input[index] == '|' || s->input[index] == '&')
				type = check_logical_operator(s->input, &index);
			if (type != skip)
				return (index);
			if (s->input[index] == '(')
				index = get_end_brac(s->input, index) - 1;
			index ++;
		}
	}
	return (index);
}

int	do_bash(t_shell *s, int *index)
{
	int	i;
	int	type;

	i = *index;
	type = 0;
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
	i = check_next_proc(s, i, type);
	*index = i;
	return (0);
}

int	bash(t_shell *s)
{
	int	i;

	i = 0;
	while (s->input[i])
		do_bash(s, &i);
	return (0);
}
