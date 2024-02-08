/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:47:20 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/08 15:09:14 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_line(t_shell *s, char *cmd, int *equal)
{
	int	i;

	i = 0;
	if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
		return (handle_error(s, 1), invalid_errmsg(cmd), 1);
	while (cmd[++ i])
	{
		if (!ft_isalpha(cmd[i]) && cmd[i] != '=' && \
			!ft_isdigit(cmd[i]) && cmd[i] != '_')
			return (handle_error(s, 1), invalid_errmsg(cmd), 1);
		if (equal)
		{
			if (cmd[i] == '=')
			{
				*equal = i;
				break ;
			}
		}
	}
	if (equal && !(*equal))
		return (1);
	return (0);
}

static void	empty_export(int ref, t_env *env)
{
	int		fd;
	t_env	*ptr;

	fd = 1;
	if (ref)
		fd = ref;
	ptr = env;
	while (ptr)
	{
		write(fd, "declare -x ", 11);
		write(fd, ptr->key, ft_strlen(ptr->key));
		write(fd, "=\"", 2);
		write(fd, ptr->value, ft_strlen(ptr->value));
		write(fd, "\"\n", 2);
		ptr = ptr->next;
	}
}

static void	transfer_value(t_env *target, t_env *new)
{
	free(target->value);
	target->value = new->value;
	new->value = NULL;
	free_env_node(new);
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
			transfer_value(ptr, new);
	}
	if (i > 1)
		return (0);
	return (empty_export(s->check, s->env), 0);
}
