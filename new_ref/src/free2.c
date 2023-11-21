/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:50:32 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/21 09:51:14 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_process(t_proc *p)
{
	if (!p)
		return ;
	free_strs(p->cmd);
	free_tokens(p->here_doc);
	free_tokens(p->f_read);
	free_tokens(p->f_out);
	free(p);
}

void	free_processes(t_proc *p)
{
	t_proc *tmp;

	while (p)
	{
		tmp = p;
		p = p->next;
		free_process(tmp);
	}
}

void	free_process_section(t_shell *s)
{
	free_processes(s->process_section.proc);
	free(s->process_section.pfd);
	free(s->process_section.pid);
	s->process_section = (t_block){0, 0, 0, 0, 0, 0, 0};
}

void	free_all(t_shell *s)
{
	free_strs(s->path);
	// free_blocks(s->input);
	free(s->root.root_msg);
	free(s->root.prompt);
	free_process_section(s);
}