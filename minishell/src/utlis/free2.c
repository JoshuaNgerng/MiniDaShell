/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:41:41 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/01 04:19:14 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_process(t_proc *p)
{
	if (!p)
		return ;
	free_tokens(p->cmd);
	free_tokens(p->here_doc);
	free_tokens(p->f_read);
	free_tokens(p->f_out);
	free(p);
}

void	free_processes(t_proc *p)
{
	t_proc	*tmp;

	while (p)
	{
		tmp = p;
		p = p->next;
		free_process(tmp);
	}
}

void	free_sect(t_sect *sec)
{
	free_processes(sec->block);
	free(sec);
}

void	free_sect_list(t_sect *list)
{
	t_sect	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free_sect(tmp);
	}
}
