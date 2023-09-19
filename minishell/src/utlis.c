/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:01:41 by jngerng           #+#    #+#             */
/*   Updated: 2023/08/22 13:01:41 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dev_print_data(t_data *d)
{
	int	i;

	while (d)
	{
		i = -1;
		while (d->cmd[++ i])
			printf("test %d cmd: %s\n", i, d->cmd[i]);
		i = -1;
		while (d->f_read[++ i])
			printf("test %d file_read: %s\n", i, d->f_read[i]);
		i = -1;
		while (d->here_doc[++ i])
			printf("test %d here_doc: %s\n", i, d->here_doc[i]);
		i = -1;
		while (d->f_write[++ i])
			printf("test %d file_write: %s\n", i, d->f_write[i]);
		i = -1;
		while (d->f_append[++ i])
			printf("test %d file_append: %s\n", i, d->f_append[i]);
		d = d->next;
	}
}

void	dev_print_proc(t_proc *p)
{
	while (p)
	{
		printf("test proc type:%c num:%d add:%d\n", p->type, p->num, p->add);
		dev_print_data(p->data);
		p = p->next;
	}
}

int	ft_checkset(char const s, char const *set)
{
	while (*set)
	{
		if (*set == s)
			return (1);
		set ++;
	}
	return (0);
}

void	dev_print_tokens(t_tokens *t)
{
	while (t)
	{
		printf("tokens: %s, type %c\n", t->token, t->type);
		t = t->next;
	}
}