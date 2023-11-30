/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:30:13 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/30 23:19:41 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
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
*/

int	process_child(t_shell *s, t_processor *p, t_proc *proc)
{
	return (0);
}

// process children need to reset pid index
int	process_children(t_shell *s, t_processor *p, t_sect *sect)
{
	t_proc	*ptr;

	p->index_p = 0;
	if (prepare_pipes())
		return (1);
	ptr = sect->block;
	while (ptr)
	{
		if (process_child(s, p, ptr))
			return (1);
		p->index_p ++;
		ptr = ptr->next;
	}
	// close pipes then waitpid
	return (0);
}

t_sect	*get_next_process(t_shell *s, t_sect *buffer, int type)
{
	int		skip;
	t_sect	*ptr;

	skip = 0;
	if (type == _or && !s->status)
		skip = type;
	else if (type == _and && s->status)
		skip = type;
	if (skip)
	{
		while (buffer && buffer->operator != skip)
		{
			ptr = buffer;
			buffer = buffer->next;
			free_sect(buffer);
		}
	}
	return (buffer);
}

int	bash(t_shell *s)
{
	int			type;
	t_processor	*p;
	t_sect		*ptr;

	p = &s->processor;
	if (tokenize_and_sectioning(s, p))
		return (1);
	p->here_doc_pipe = (int *) malloc(p->here_doc_num * sizeof(int) * 2);
	if (!p->here_doc_pipe || do_here_doc(s, p))
		return (1);
	while (p->buffer)
	{
		ptr = p->buffer;
		p->buffer = p->buffer->next;
		type = p->buffer->operator;
		p->pid = (int *) malloc(ptr->pid * sizeof(int));
		p->pipe = (int *) malloc(ptr->pid * sizeof(int) * 2);
		if (!p->pid || !p->pipe)
			return (1);
		if (expand(s, ptr) || process_children(s, &p, ptr))
			return (1);
		p->buffer = get_next_process(s, p->buffer, type);
	}
	return (0);
}
