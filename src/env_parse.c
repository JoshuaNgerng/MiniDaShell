/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:49:54 by mukhairu          #+#    #+#             */
/*   Updated: 2023/11/13 18:19:47 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Test
t_env	*get_env_state(char **env)
{
	int		i;
	t_env	*temp;
	t_env	*list;
	// char	**str;

	i = 0;
	list = NULL;
	if (!env)
		return (NULL);
	while(env[i])
	{
		temp = ft_env_new(env[i]);
		ft_env_addback(&list, temp);
		// free(str);
		i++;
	}
	// print_env(temp);
	return (list);
}

void	print_env(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		printf("%s=", temp->key);
		printf("%s\n", temp->value);
		temp = temp->next;
	}
}

//add new node, put new node in list, delete list
