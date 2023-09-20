/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 05:31:57 by jngerng           #+#    #+#             */
/*   Updated: 2023/08/18 05:31:57 by jngerng          ###   ########.fr       */
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

void	free_tokens(t_tokens *t)
{
	t_tokens	*temp;

	while (t)
	{
		temp = t;
		t = t->next;
		if (temp->token)
			free(temp->token);
		free(temp);
	}
}

void	free_data(t_data *d)
{
	int		i;
	t_data	*f;

	while (d)
	{
		f = d;
		d = d->next;
		free_strs(f->cmd);
		free_strs(f->f_read);
		free_strs(f->here_doc);
		i = -1;
		while (f->f_out[++ i].f_name)
			free(f->f_out[i].f_name);
		free(f->f_out);
		free(f);
	}
}

void	free_proc(t_proc *p)
{
	t_proc	*tmp;

	while (p)
	{
		tmp = p;
		p = p->next;
		free_data(tmp->data);
		free(tmp->pfd);
		free(tmp->pid);
		free(tmp);
	}
}

void	free_all(t_shell *s)
{
	if (s->process)
		free_proc(s->process);
	free_strs(s->path);
	rl_clear_history();
}
