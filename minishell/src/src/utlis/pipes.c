/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:07:59 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/01 03:57:59 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (pipe(&pipes[i * 2]) == -1)
			return (close_pipes(pipes, i), 1);
	}
	return (0);
}

void	clear_pipes(t_processor *p)
{
	if (!p->pipe)
		return ;
	close_pipes(p->pipe, p->pipe_num);
	free(p->pipe);
	p->pipe = NULL;
}

void	clear_here_doc(t_processor *p)
{
	if (!p->here_doc_pipe)
		return ;
	while (p->index_h < p->here_doc_num)
	{
		close(p->here_doc_pipe[p->index_h * 2]);
		close(p->here_doc_pipe[p->index_h * 2 + 1]);
		p->index_h ++;
	}
	free(p->here_doc_pipe);
	p->here_doc_pipe = NULL;
}
