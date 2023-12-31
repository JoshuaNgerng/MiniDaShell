/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:13:02 by jngerng           #+#    #+#             */
/*   Updated: 2023/12/01 16:33:33 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dev_print_strs(char **s)
{
	int	i;

	i = -1;
	while (s[++ i])
		printf("%s\n", s[i]);
}

void	dev_print_tokens(t_token *t)
{
	while (t)
	{
		printf("test str: %s, type: %d\n", t->token, t->type);
		t = t->next;
	}
}

void	dev_print_proc_list(t_proc *p)
{
	while (p)
	{
		printf("test cmd\n");
		dev_print_tokens(p->cmd);
		printf("test here_doc\n");
		dev_print_tokens(p->here_doc);
		printf("test read\n");
		dev_print_tokens(p->f_read);
		printf("test out\n");
		dev_print_tokens(p->f_out);
		p = p->next;
	}
}

void	dev_print_sect(t_sect *sec)
{
	while (sec)
	{
		dev_print_proc_list(sec->block);
		printf("operator type (%d), pid (%d)\n", sec->operator, sec->pid);
		sec = sec->next;
	}
}

void	dev_print_processor(t_processor p)
{
	dev_print_sect(p.buffer);
	printf("here_doc index (%d), pipe/pid_index (%d)\n", p.index_h, p.index_p);
	printf("no of pipes (%d), no of here_doc (%d) \n", p.pipe_num, p.here_doc_num);
}