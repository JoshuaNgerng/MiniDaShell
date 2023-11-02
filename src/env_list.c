/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:50:25 by mukhairu          #+#    #+#             */
/*   Updated: 2023/11/03 07:42:03 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_env_new(char *key, char *value)
{
	t_env *list;

	list = (t_env *)malloc(sizeof(t_env));
	if (!list)
		return (NULL);
	list->key = key;
	list->value = value;
	list->next = NULL;
	return (list);
}

void	ft_env_addback(t_env **list, t_env *new)
{
	t_env	*temp;

	if (!list)
		return ;
	if (!*list)
		*list = new;
	else
	{
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
