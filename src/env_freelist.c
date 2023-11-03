/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_freelist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:00:21 by mukhairu          #+#    #+#             */
/*   Updated: 2023/11/03 17:11:09 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_1(t_env *list)
{
	t_env	*temp;

	if (!list)
		return ;
	temp = list;
	free(temp->key);
	free(temp->value);
	free(temp);
}


void	free_all_env(t_env *list)
{
	t_env *temp;

	if (!list)
		return ;
	while (list != NULL)
	{
		temp = list;
		list = list->next;
		free_env_1(temp);
	}
}