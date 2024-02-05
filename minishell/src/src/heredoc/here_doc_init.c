/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:00:33 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/01 03:28:56 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_here_doc_num_proc(t_proc *p)
{
	int		out;
	t_token	*ptr;

	out = 0;
	ptr = p->here_doc;
	while (ptr)
	{
		out ++;
		ptr = ptr->next;
	}
	return (out);
}

static int	get_here_doc_num(t_processor *p)
{
	int		out;
	t_sect	*ptr;
	t_proc	*ptr2;

	out = 0;
	ptr = p->buffer;
	while (ptr)
	{
		ptr2 = ptr->block;
		while (ptr2)
		{
			out += get_here_doc_num_proc(ptr2);
			ptr2 = ptr2->next;
		}
		ptr = ptr->next;
	}
	return (out);
}

int	do_here_doc(t_shell *s, t_processor *p)
{
	int	i;

	p->here_doc_num = get_here_doc_num(p);
	if (p->here_doc_num < 1)
		return (0);
	p->here_doc_pipe = (int *) malloc(p->here_doc_num * 2 * sizeof(int));
	if (!p->here_doc_pipe)
		return (errmsg_errno(12), handle_error(s, 137), 1);
	i = -1;
	while (++ i < p->here_doc_num)
	{
		if (pipe(&p->here_doc_pipe[i * 2]))
			return (close_pipes(p->here_doc_pipe, i), 1);
	}
	if (loop_here_doc(s, p, p->here_doc_pipe))
		return (close_pipes(p->here_doc_pipe, i), 1);
	return (0);
}
