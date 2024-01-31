/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:23:05 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/01 03:16:03 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_section(t_shell *s, t_sect *target)
{
	t_processor	*p;
	t_proc		*ptr;

	p = &s->processor;
	if (p->here_doc_pipe)
	{
		if (!target->block->here_doc)
		{
			free_sect(target);
			return ;
		}
		ptr = target->block;
		while (ptr)
		{
			if (ptr->here_doc)
			{
				close(p->here_doc_pipe[p->index_h * 2]);
				close(p->here_doc_pipe[p->index_h * 2 + 1]);
				p->index_h ++;
			}
			ptr = ptr->next;
		}
	}
	free_sect(target);
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
		while (buffer && buffer->operator == skip)
		{
			ptr = buffer;
			buffer = buffer->next;
			clear_section(s, ptr);
		}
		if (buffer)
		{
			ptr = buffer;
			buffer = buffer->next;
			clear_section(s, ptr);
		}
	}
	return (buffer);
}

void	cont_section_list(t_sect *new, t_ptr_s *ptr)
{
	if (!ptr->head)
	{
		ptr->head = new;
		ptr->tail = ptr->head;
	}
	else
	{
		ptr->tail->next = new;
		ptr->tail = ptr->tail->next;
	}
	ptr->tail->next = NULL;
}

int	add_section(t_shell *s, t_ptr_s	*ptr, int *index)
{
	int		type;
	t_sect	*new;
	t_ptr_p	buffer;

	buffer = (t_ptr_p){0, 0};
	new = (t_sect *) malloc(sizeof(t_sect));
	if (!new)
		return (1);
	new->pid = 0;
	type = 0;
	while (s->input[*index] && !(type & LOGIC))
	{
		type = add_process(s, &buffer, new, index);
		if (type < 0)
			return (1);
	}
	new->operator = type;
	new->block = buffer.head;
	cont_section_list(new, ptr);
	return (0);
}

int	tokenize_and_sectioning(t_shell *s, t_processor	*p)
{
	int		index;
	t_ptr_s	buffer;

	index = 0;
	buffer = (t_ptr_s){0, 0};
	while (s->input[index])
	{
		if (add_section(s, &buffer, &index))
			return (free_sect_list(buffer.head), 1);
	}
	p->buffer = buffer.head;
	return (0);
}
