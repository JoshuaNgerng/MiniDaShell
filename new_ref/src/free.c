/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:29:09 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/08 20:04:22 by jngerng          ###   ########.fr       */
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

void	free_block(t_block *b)
{
	if (!b)
		return ;
	free_tokens(b->tokens)
	free(b);
}

void	free_blocks(t_block *b)
{
	t_block *tmp;

	while (b)
	{
		tmp = s;
		b = b->next;
		free_block(tmp);
	}
}
