/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:24:41 by jngerng           #+#    #+#             */
/*   Updated: 2024/01/31 17:53:08 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_equal_sign(char *s)
{
	int	i;

	i = -1;
	while (s[++ i])
	{
		if (s[i] == '=')
			return (i);
	}
	return (-i);
}

void	env_list_addback(t_env **list, t_env *new)
{
	t_env	*temp;

	if (!new)
		return ;
	if (!(*list))
		*list = new;
	else
	{
		temp = *list;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->next = NULL;
		new->prev = temp;
	}
}

t_env	*search_env(t_env *head, char *key, int len)
{
	int		test_len;
	t_env	*ptr;

	ptr = head;
	while (ptr)
	{
		test_len = ft_strlen(ptr->key);
		if (!ft_strncmp(ptr->key, key, len) && len == test_len)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

// put errmsg
t_env	*make_env_node(char *env, int equal)
{
	t_env	*new;

	if (equal < 0)
		return (NULL);
	new = (t_env *) malloc(sizeof(t_env));
	if (!new)
		return (errmsg_errno(8), NULL);
	new->key = ft_substr(env, 0, equal);
	if (!new->key)
		return (errmsg_errno(8), free(new), NULL);
	new->value = ft_strdup(&env[equal + 1]);
	if (!new->value)
		return (errmsg_errno(8), free(new->key), free(new), NULL);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_env	*env_list_init(char **env)
{
	int		i;
	int		equal;
	t_env	*head;
	t_env	*ptr;
	t_env	*new;

	i = 0;
	head = make_env_node(env[0], find_equal_sign(env[0]));
	if (!head)
		return (NULL);
	ptr = head;
	while (env[++ i])
	{
		equal = find_equal_sign(env[i]);
		if (equal < 0)
			continue ;
		new = make_env_node(env[i], equal);
		ptr->next = new;
		new->prev = ptr;
		if (!new)
			return (free_env_list(head), NULL);
		ptr = ptr->next;
	}
	ptr->next = NULL;
	return (head);
}
