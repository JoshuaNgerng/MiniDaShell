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

void	free_all(t_shell *s)
{
	int	i;

	i = -1;
	while (++ i < s->num)
	{
		free_strs(s->data[i].cmd);
		free_strs(s->data[i].file_read);
		free_strs(s->data[i].here_doc);
		free_strs(s->data[i].file_write);
		free_strs(s->data[i].file_append);
	}
	free(s->data);
	if (s->pid)
		free(s->pid);
	if (s->pfd)
		free(s->pfd);
	*s = (t_shell){0, 0, 0, 0};
}
