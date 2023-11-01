/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_linklist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:50:25 by mukhairu          #+#    #+#             */
/*   Updated: 2023/10/25 18:59:26 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_env_new(char *key, char *value)
{
	t_env *list;

	list = (t_env *)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->key = key;
	list->value = value;
	list->next = NULL;
	return (list);
}

t_env	ft_env_add(t_env **list, t_list *new)
{
	if (!list || !new)
		return ;
	new -> next = *list;
	*list = new;
}
