/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:42:42 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/21 17:07:57 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	transfer_token(t_proc *new, t_token *t)
{
	if (t->type == here_doc)
		;
	else if (t->type == _read)
		;
	else if (t->type == _write || t->type == _append)
		;
}

int	transfer_token_buffer(t_buffer *b, t_token *t)
{
	return (0);
}

int	get_process_node(t_proc **ptr, t_block *b, t_token *t)
{
	t_token		*f_ptr;
	t_proc 		*new;
	t_buffer	buffer;

	buffer = (t_buffer){0, 0, 0};
	*ptr = NULL;
	new = (t_proc *) malloc(sizeof(t_proc));
	if (!new)
		return (errmsg_errno(5), 1);
	while (t)
	{
		transfer_token_buffer(&buffer, t);
		f_ptr = t;
		free(f_ptr);
		t = t->next;
	}
	new->cmd = (char **) malloc(sizeof(char *));
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