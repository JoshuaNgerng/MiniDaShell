/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:50:25 by mukhairu          #+#    #+#             */
/*   Updated: 2023/11/14 17:51:34 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_env_new(char *env)
{
	int		i;
	t_env	*list;

	list = malloc(sizeof(t_env));
	if (!list)
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
		i ++;
	list->key = ft_substr(env, 0, i);
	if (!list->key)
	{
		free(list);
		return (NULL);
	}
	list->value = ft_strdup(&env[i + 1]);
	if (!list->value)
	{
		free(list);
		free(list->key);
		return (NULL);
	}
	list->next = NULL;
	return (list);
}

void	ft_env_addback(t_env **list, t_env *new)
{
	t_env	*temp;

	if (!new)
		return ;
	if (!*list)
		*list = new;
	else
	{
		temp = *list;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

void	ft_env_add(t_env **list, t_env *new)
{
	if (!list || !new)
		return ;
	new->next = *list;
	*list = new;
}
