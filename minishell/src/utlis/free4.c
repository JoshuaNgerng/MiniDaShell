/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:18:34 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/07 11:56:58 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset_struct_var(t_shell *s)
{
	s->processor.pid = NULL;
	s->processor.pipe = NULL;
	s->processor.here_doc_pipe = NULL;
	s->processor.here_doc_num = 0;
	s->processor.pipe_num = 0;
	s->processor.index_h = 0;
	s->processor.index_p = 0;
	s->processor.stdin_ = 0;
	s->processor.stdout_ = 1;
}

void	free_reset(t_shell *s)
{
	s->check = 0;
	if (s->input)
		free(s->input);
	s->input = NULL;
	free_strs(s->processor.path);
	s->processor.path = NULL;
	free_strs(s->processor.env);
	s->processor.env = NULL;
	free_sect_list(s->processor.buffer);
	s->processor.buffer = NULL;
	if (s->processor.pid)
		free(s->processor.pid);
	if (s->processor.pipe)
		free(s->processor.pipe);
	if (s->processor.here_doc_pipe)
		free(s->processor.here_doc_pipe);
	reset_struct_var(s);
}

void	free_reset_pipe_pid(t_processor *p)
{
	free(p->pid);
	p->pid = NULL;
	free(p->pipe);
	p->pipe = NULL;
}
