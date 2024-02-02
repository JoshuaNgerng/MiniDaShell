/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:47:20 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/02 09:12:23 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_line(t_shell *s, char *cmd, int *equal)
{
	int	i;

	i = -1;
	while (cmd[++ i])
	{
		if (ft_checkset(cmd[i], "$*&^"))
			return (handle_error(s, 1), invalid_errmsg(cmd), 1);
		if (equal)
		{
			if (cmd[i] == '=')
				*equal = i;
		}
	}
	if (equal && !(*equal))
		return (1);
	return (0);
}

static void	empty_export(t_env *env, int i)
{
	t_env	*ptr;

	if (i > 1)
		return ;
	ptr = env;
	while (ptr)
	{
		write(1, "declare -x ", 11);
		write(1, ptr->key, ft_strlen(ptr->key));
		write(1, "=", 1);
		write(1, ptr->value, ft_strlen(ptr->value));
		write(1, "\n", 1);
		ptr = ptr->next;
	}
}

int	export(t_shell *s, char **cmd)
{
	int		i;
	int		equal;
	t_env	*new;
	t_env	*ptr;

	i = 0;
	while (cmd[++ i])
	{
		equal = 0;
		if (check_valid_line(s, cmd[i], &equal))
			continue ;
		new = make_env_node(cmd[i], equal);
		if (!new)
			return (handle_error(s, 137), 1);
		ptr = search_env(s->env, new->key, ft_strlen(new->key));
		if (!ptr)
			env_list_addback(&s->env, new);
		else
		{
			ptr->value = new->value;
			new->value = NULL;
			free_env_node(new);
		}
	}
	return (empty_export(s->env, i), 0);
}

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
