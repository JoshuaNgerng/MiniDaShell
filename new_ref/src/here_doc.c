/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:15:19 by jngerng           #+#    #+#             */
/*   Updated: 2023/12/01 16:46:59 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_here_doc_num(t_processor *p)
{
	int		out;
	t_sect	*ptr;
	t_token	*ptr2;

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

void	close_pipes_err(int *pipes, int len)
{
	int	i;
	int	j;

	while (++ i < len)
	{
		j = i * 2;
		close(pipes[j]);
		close(pipes[j + 1]);
	}
}

int	do_here_doc(t_shell *s, t_processor *p)
{
	int	i;

	p->here_doc_num = get_here_doc_num(p);
	p->here_doc_pipe = (int *) malloc(p->here_doc_num * 2 * sizeof(int));
	if (!p->here_doc_pipe)
		return (1);
	i = -1;
	while (++ i < p->here_doc_num)
	{
		if (pipe(&p->here_doc_pipe[i * 2]))
			return (close_pipes_err(p->here_doc_pipe, i), 1);
	}
	if (loop_here_doc(s, p, p->here_doc_pipe))
		return (close_pipes_err(p->here_doc_pipe, i), 1);
	return (0);
}
