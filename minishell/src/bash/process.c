/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:58:22 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/01 03:15:42 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cont_proc_list(t_proc *new, t_buffer buffer, t_ptr_p *ptr)
{
	new->cmd = buffer.cmd.head;
	new->here_doc = buffer.here_doc.head;
	new->f_read = buffer.read.head;
	new->f_out = buffer.out.head;
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

void	transfer_token_buffer(t_proc *p, t_buffer *b, t_token *t)
{
	if (t->type == here_doc)
	{
		transfer_token_ptr(&b->here_doc, t);
		p->in = here_doc;
	}
	else if (t->type & _read)
	{
		transfer_token_ptr(&b->read, t);
		p->in = _read;
	}
	else if (t->type & _write || t->type & _append)
		transfer_token_ptr(&b->out, t);
	else
		transfer_token_ptr(&b->cmd, t);
}

static void	loop_token_list(t_proc *p, t_token *list, t_buffer *buffer)
{
	t_token	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		transfer_token_buffer(p, buffer, temp);
	}
}

int	add_process(t_shell *s, t_ptr_p *ptr, t_sect *sec, int *index)
{
	int			type;
	t_token		*list;
	t_proc		*new;
	t_buffer	buffer;

	buffer = (t_buffer){(t_ptr){0, 0}, (t_ptr){0, 0}, \
						(t_ptr){0, 0}, (t_ptr){0, 0}};
	type = 0;
	list = NULL;
	if (tokenize_input(s, &list, index, &type))
		return (-1);
	if (!list)
		return (0);
	sec->pid ++;
	new = (t_proc *) malloc(sizeof(t_proc));
	if (!new)
		return (free_tokens(list), handle_error(s, 137), errmsg_errno(5), -1);
	new->in = 0;
	loop_token_list(new, list, &buffer);
	return (cont_proc_list(new, buffer, ptr), type);
}
