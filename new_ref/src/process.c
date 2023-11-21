/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:42:42 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/21 22:41:08 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	transfer_token_ptr(t_ptr *p, t_token *t)
{
	if (!p)
	{
		p->head = t;
		p->tail = p->head;
		p->tail->next = NULL;
		return ;
	}
	else
		p->tail->next = t;
	p->tail = p->tail->next;
	p->tail->next = NULL;
}

void	transfer_token_buffer(t_proc *p, t_buffer *b,  t_block *block, t_token *t)
{
	if (t->type == here_doc)
	{
		transfer_token_ptr(&b->here_doc, t);
		p->in = here_doc;
		block->add ++;
	}
	else if (t->type == _read)
	{
		transfer_token_ptr(&b->read, t);
		p->in = _read;
	}
	else if (t->type == _write || t->type == _append)
		transfer_token_ptr(&b->out, t);
	else
	{
		transfer_token_ptr(&b->cmd, t);
		b->size ++;
	}
	return (0);
}

void	transfer_token_proc(t_proc *new, t_buffer buffer)
{
	int		i;
	t_token	*ptr;

	new->here_doc = buffer.here_doc.head;
	new->f_read = buffer.read.head;
	new->f_out = buffer.out.head;
	if (!new->cmd)
	{
		free_tokens(buffer.cmd.head);
		return ;
	}
	i = -1;
	while (++ i < buffer.size)
	{
		new->cmd[i] = buffer.cmd.head->token;
		ptr = buffer.cmd.head;
		buffer.cmd.head = buffer.cmd.head->next;
	}
}

int	get_process_node(t_proc **ptr, t_block *b, t_token *t)
{
	t_proc		*new;
	t_buffer	buffer;

	buffer = (t_buffer){0, (t_ptr){0, 0}, (t_ptr){0, 0}, \
						(t_ptr){0, 0}, (t_ptr){0, 0}};
	*ptr = NULL;
	new = (t_proc *) malloc(sizeof(t_proc));
	if (!new)
		return (errmsg_errno(5), 1);
	b->num ++;
	while (t)
	{
		transfer_token_buffer(new, &buffer, b, t);
		t = t->next;
	}
	new->cmd = (char **) malloc((buffer.size + 1) * sizeof(char *));
	transfer_token_proc(new, buffer);
	if (!new->cmd)
	{
		*ptr = NULL;
		return (free(new), 1);
	}
	*ptr = new;
	return (0);
}

int	process_init(t_shell *s, int *i, int *type)
{
	int		i;
	t_token	*buffer;
	t_proc	*ptr;

	buffer = tokenize_input(s, i, type);
	if (!buffer)
		return (1);
	if (get_process_node(&s->process_section.proc, &s->process_section, buffer))
		return (1);
	ptr = s->process_section.proc;
	while (s->input[*i] && *type & LOGIC)
	{
		buffer = tokenize_input(s, i, type);
		if (!buffer)
			return (free_process_section(s), 1);
		if (get_process_node(&s->process_section.proc->next, &s->process_section, buffer))
			return (free_process_section(s), 1);
		s->process_section.proc = s->process_section.proc->next;
	}
	s->process_section.proc->next = NULL;
	return (0);
}