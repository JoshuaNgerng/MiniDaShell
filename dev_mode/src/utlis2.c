/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 08:41:32 by jngerng           #+#    #+#             */
/*   Updated: 2023/12/01 16:42:11 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strcpy_index(char *dst, int start, char *src)
{
	int	len;

	len = -1;
	while (src[++ len])
		dst[start + len] = src[len];
	return (len);
}

void	transfer_token_ptr(t_ptr *p, t_token *t)
{
	if (!(p->tail))
	{
		p->head = t;
		p->tail = p->head;
		p->tail->next = NULL;
		return ;
	}
	p->tail->next = t;
	p->tail = p->tail->next;
	p->tail->next = NULL;
}

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

void	close_pipes(int *pipes, int len)
{
	int	i;
	int	j;

	i = -1;
	while (++ i < len)
	{
		j = i * 2;
		close(pipes[j]);
		close(pipes[j + 1]);
	}
}

int	prepare_pipes(int *pipes, int len)
{
	int	i;

	i = -1;
	while (++ i < len)
	{
		if (pipe(&pipes[i * 2]))
			return (close_pipes(pipes, i), 1);
	}
	return (0);
}

void	handle_error(t_shell *s, int ext_code)
{
	s->status = ext_code;
	s->check = 1;
}
