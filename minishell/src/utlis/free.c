/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:41:34 by jngerng           #+#    #+#             */
/*   Updated: 2024/01/20 18:45:42 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_strs(char **s)
{
	int	i;

	if (!s)
		return ;
	i = -1;
	while (s[++ i])
		free(s[i]);
	free(s);
}

void	free_token(t_token *t)
{
	if (!t)
		return ;
	if (t->token)
		free(t->token);
	free(t);
}

void	free_tokens(t_token *t)
{
	t_token	*tmp;

	while (t)
	{
		tmp = t;
		t = t->next;
		free_token(tmp);
	}
}

void	free_tokens_empty(t_token *t)
{
	t_token	*tmp;

	while (t)
	{
		tmp = t;
		t = t->next;
		free(tmp);
	}
}

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
