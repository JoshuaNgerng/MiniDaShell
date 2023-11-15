/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:35:06 by mukhairu          #+#    #+#             */
/*   Updated: 2023/11/15 15:25:14 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*chk_key(t_env *list, char *str)
{
	t_env	*temp;

	temp = list;
	while (temp)
	{
		if (!ft_strncmp(temp->key, str, ft_strlen(str)))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	export(t_env *list, char *str)
{
	t_env	*temp;
	t_env	*check;
	char	**splitted;
	int		i;
	
	i = -1;
	splitted = ft_split(str, ' ');
	while (splitted[++i])
	{
		if (!chk_stx(splitted[i], 1))
			continue ;
		temp = ft_env_new(splitted[i]);
		check = chk_key(list, temp->key);
		if (!check)
		{
			ft_env_addback(&list, temp);
			continue ;
		}
		check->value = temp->value;
		free(temp->key);
		free(temp);
	}
	free2d(splitted);
}

/*
ptr
check

i = 1
buffer = ft_split;
while (buffer[i])
{
	chk_stx();
	// if syntax correct
	ptr = env new
	check = chk_key(ptr->key)
	// if not exist
	env add back
	// if exist
	check->value = ptr->value (update val)
	free(ptr->key) free key first
	free(ptr) free link list 
}
free buffer (free char **)
*/