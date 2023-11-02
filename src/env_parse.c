/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:49:54 by mukhairu          #+#    #+#             */
/*   Updated: 2023/11/03 07:42:06 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Test
t_env	*get_env_state(char **env)
{
	int	i;
	t_env	*temp;
	t_env	*list;
	char	**str;

	i = 0;
	list = NULL;
	// if (!env)
	// 	return ;
	while(env[i])
	{
		str = ft_split(env[i], '=');
		temp = ft_env_new(str[0], str[1]);
		ft_env_addback(&list, temp);
		// list = ft_env_new()
		i++;
	}
	return (list);
}

//add new node, put new node in list, delete list
