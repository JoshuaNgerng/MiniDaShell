/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:17:50 by mukhairu          #+#    #+#             */
/*   Updated: 2023/11/13 19:31:51 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*unset_proc(t_env *list, t_env *current)
{
	t_env	*head;
	t_env	*temp1;
	t_env	*temp2;

	if (!list && !current)
		return (NULL);
	head = list;
	temp1 = head;
	if (head == current)
	{
		temp1 = head->next;
		free_env_1(current);
		head = temp1;
		return (head);
	}
	while (temp1->next != current)
		temp1 = temp1->next;
	if (current->next == NULL)
	{
		free_env_1(current);
		temp1->next = NULL;
		return (head);
	}
	temp2 = current->next;
	temp1->next = temp2;
	free_env_1(current);
	return (head);
}

t_env	*unset(t_env *list, char *input)
{
	t_env	*temp;
	char	**key;
	int		i;

	temp = list;
	i = 0;
	key = ft_split(input, ' ');
	while (key[i])
	{
		temp = chk_key(temp, key[i]);
		if (!temp)
		{
			temp = list;
			i++;
			continue ;
		}
		list = unset_proc(list, temp);
		temp = list;
		i++;
	}
	free2d(key);
	return (temp);
}
