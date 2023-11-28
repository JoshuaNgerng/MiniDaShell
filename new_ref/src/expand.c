/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:17:32 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/28 17:27:27 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_cmd(t_shell *s, t_token *t)
{
	t_token	*ptr;

	
	return (0);
}

int	expand(t_shell *s, t_buffer *b)
{
	if (b->cmd.head)
	{
		if (expand_cmd(s, b->cmd.head))
			return (1);
	}
	if (b->here_doc.head)
	{
		if (expand_here_doc(s, b->here_doc.head))
			return (1);
	}
	if (b->read.head)
	{
		if (expand_files(s, b->read.head))
			return (1);
	}
	if (b->out.head)
	{
		if (expand_files(s, b->out.head))
			return (1);
	}
	return (0);
}