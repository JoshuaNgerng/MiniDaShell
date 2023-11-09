/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:35:06 by mukhairu          #+#    #+#             */
/*   Updated: 2023/11/09 16:51:50 by mukhairu         ###   ########.fr       */
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
	char	*key;
	char	*val;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	key = ft_substr(str, 0, i);
	if (!str[i]) // if i reach end of string
		val =  ft_strdup("");
	else
		val = ft_strdup(&str[i + 1]);
	temp = chk_key(list, key);
	if (!temp)
	{
		//add check for value here

		//
		temp = ft_env_new(str);
		ft_env_addback(&list, temp);
		// handle memory leak
		free(key);
		free(val);
		return ;
	}
	free(temp->value);
	temp->value = val;
	free(key);
}
