/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:00:33 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/07 12:08:03 by jngerng          ###   ########.fr       */
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

int	here_doc_child_proc(t_shell *s, t_processor *p)
{
	int	pid;
	int	check;

	pid = fork();
	if (pid < 0)
		return (errmsg_errno(20), 1);
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		check = loop_here_doc(s, p, p->here_doc_pipe);
		close_pipes(p->here_doc_pipe, p->here_doc_num);
		if (check && !s->status)
			s->status = 1;
		free_all_exit(s, s->status);
	}
	else
	{
		waitpid(pid, &s->status, 0);
		s->status = WEXITSTATUS(s->status);
	}
	return (0);
}

int	do_here_doc(t_shell *s, t_processor *p)
{
	int	i;

	p->index_h = 0;
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
	if (here_doc_child_proc(s, p))
		return (1);
	if (s->status || g_ctrl_c)
		return (1);
	return (0);
}
