/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:30:13 by jngerng           #+#    #+#             */
/*   Updated: 2023/12/04 22:05:53 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_children(t_shell *s, t_processor *p, t_sect *sect)
{
	int		i;
	t_proc	*store;

	p->index_p = 0;
	if (sect->pid == 1)
		return (check_special_process(s, p, sect->block));
	if (prepare_pipes(p->pipe, p->pipe_num))
		return (1);
	while (sect->block)
	{
		store = sect->block;
		sect->block = sect->block->next;
		store->next = NULL;
		if (process_child(s, p, store))
			return (1);
		free_process(store);
		p->index_p ++;
	}
	close_pipes(p->pipe, p->pipe_num);
	close_pipes(p->here_doc_pipe, p->here_doc_num);
	i = -1;
	while (++ i < sect->pid)
		waitpid(p->pid[i], &s->status, 0);
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
			free_sect(ptr);
		}
		if (buffer)
		{
			ptr = buffer;
			buffer = buffer->next;
			free_sect(ptr);
		}
	}
	return (buffer);
}

int	bash_helper(t_shell *s, t_processor *p)
{
	p->pipe_num = p->buffer->pid - 1;
	p->pid = (int *) malloc(p->buffer->pid * sizeof(int));
	p->pipe = (int *) malloc(p->pipe_num * sizeof(int) * 2);
	if (!p->pid || !p->pipe)
		return (handle_error(s, 137), 1);
	if (expand(s, p->buffer))
		return (1);
	if (process_children(s, p, p->buffer))
		return (1);
	if (p->pid)
		free(p->pid);
	p->pid = NULL;
	if (p->pipe)
		free(p->pipe);
	p->pipe = NULL;
	return (0);
}

int	bash(t_shell *s)
{
	int			type;
	t_processor	*p;
	t_sect		*ptr;

	p = &s->processor;
	if (tokenize_and_sectioning(s, p))
		return (1);
	if (do_here_doc(s, p))
		return (1);
	while (p->buffer)
	{
		type = p->buffer->operator;
		if (bash_helper(s, p))
			return (1);
		ptr = p->buffer;
		p->buffer = p->buffer->next;
		free_sect(ptr);
		p->buffer = get_next_process(s, p->buffer, type);
	}
	return (0);
}
