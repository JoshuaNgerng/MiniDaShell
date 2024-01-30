/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:52:32 by jngerng           #+#    #+#             */
/*   Updated: 2024/01/27 09:44:58 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	transfer_token_ptr(t_ptr *p, t_token *t)
{
	if (!(p->tail))
	{
		p->head = t;
		p->tail = p->head;
		p->tail->next = NULL;
		return ;
	}
	p->tail->next = t;
	p->tail = p->tail->next;
	p->tail->next = NULL;
}

void	handle_error(t_shell *s, int ext_code)
{
	s->status = ext_code;
	s->check = 1;
}

void	detach_node(t_env **head, t_env *target)
{
	t_env	*ptr;

	if (!target->prev)
	{
		*head = target->next;
		target->next = NULL;
	}
	ptr = target->prev;
	ptr->next = target->next;
	target->next = NULL;
	target->prev = NULL;
}

char	*get_env(char **env, char *var, int len)
{
	char	**buffer;

	buffer = env;
	while (buffer)
	{
		if (!ft_strncmp(*buffer, var, len))
			return (*(buffer) + len + 1);
		buffer ++;
	}
	return (NULL);
}

char	*get_input(t_shell *s, const char *prompt)
{
	int		i;
	char	*r;

	while (1)
	{
		r = readline(prompt);
		if (!r)
		{
			if (errno == ENOMEM)
				return (handle_error(s, 137), errmsg_errno(2), NULL);
			return (NULL);
		}
		i = -1;
		while (r[++ i])
			if (r[i] != ' ')
				break ;
		if (r[i])
			break ;
		free(r);
	}
	return (r);
}
