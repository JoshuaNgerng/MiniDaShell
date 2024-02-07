/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:28:24 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/07 09:38:32 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*unset_node(t_env *head, t_env *target)
{
	t_env	*ptr;
	t_env	*ptr2;

	if (!target->prev)
	{
		head = target->next;
		head->prev = NULL;
	}
	else if (!target->next)
	{
		ptr = target->prev;
		ptr->next = NULL;
	}
	else
	{
		ptr = target->prev;
		ptr2 = target->next;
		ptr->next = ptr2;
		ptr2->prev = ptr;
	}
	free_env_node(target);
	return (head);
}

int	unset(t_shell *s, char **cmd)
{
	int		i;
	t_env	*ptr;

	i = 0;
	ptr = s->env;
	while (cmd[++ i])
	{
		ptr = search_env(s->env, cmd[i], ft_strlen(cmd[i]));
		if (!ptr)
			continue ;
		s->env = unset_node(s->env, ptr);
	}
	return (0);
}
