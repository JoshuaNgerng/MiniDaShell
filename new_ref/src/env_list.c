/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:03:32 by jngerng           #+#    #+#             */
/*   Updated: 2023/12/04 22:04:01 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	invalid_errmsg(char *cmd)
{
	int	i;

	write(2, "export: `", 9);
	i = find_equal_sign(cmd);
	if (i < 0)
		write(2, cmd, ft_strlen(cmd));
	else
		write(2, cmd, i);
	write(2, "': not a valid identifer\n", 25);
}

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
	return (0);
}

t_env	*unset_proc(t_env *head, t_env *target)
{
	t_env	*ptr;
	t_env	*ptr2;

	if (!target->prev)
	{
		head = target->next;
		head->prev = NULL;
		free_env_node(target);
	}
	else
	{
		ptr = target->prev;
		ptr2 = target->next;
		ptr->next = ptr2;
		ptr2->prev = ptr;
	}
	if (ft_strncmp(target->key, "PWD", 4) && ft_strncmp(ptr->key, "OLDPWD", 7))
		return (free_env_node(target), head);
	target->next = NULL;
	target->prev = NULL;
	return (head);
}

int	unset(t_shell *s, char **cmd)
{
	int		i;
	t_env	*ptr;

	i = -1;
	ptr = s->env;
	while (cmd[++ i])
	{
		if (check_valid_line(s, cmd[i], NULL))
			continue ;
		ptr = search_env(s->env, cmd[i], ft_strlen(cmd[i]));
		if (!ptr)
			continue ;
		s->env = unset_proc(s->env, ptr);
	}
	return (0);
}
