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

void	print_info(t_shell s)
{
	int	i;
	int	j;

	i = -1;
	while (++ i < s.num)
	{
		j = -1;
		while (s.data[i].cmd[++ j])
			printf("test %d cmd: %s\n", i, s.data[i].cmd[j]);
		j = -1;
		while (s.data[i].file_read[++ j])
			printf("test %d file_read: %s\n", i, s.data[i].file_read[j]);
		j = -1;
		while (s.data[i].here_doc[++ j])
			printf("test %d here_doc: %s\n", i, s.data[i].here_doc[j]);
		j = -1;
		while (s.data[i].file_write[++ j])
			printf("test %d file_write: %s\n", i, s.data[i].file_write[j]);
		j = -1;
		while (s.data[i].file_append[++ j])
			printf("test %d file_append: %s\n", i, s.data[i].file_append[j]);
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