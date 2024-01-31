/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:41:34 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/01 03:56:27 by jngerng          ###   ########.fr       */
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
