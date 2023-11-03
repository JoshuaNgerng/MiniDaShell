/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:49:54 by mukhairu          #+#    #+#             */
/*   Updated: 2023/11/03 17:34:09 by mukhairu         ###   ########.fr       */
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
	// if (!env)
	// 	return ;
	while(env[i])
	{
		str = ft_split(env[i], '=');
		temp = ft_env_new(str[0], str[1]);
		// printf("test %s \n", temp->key);
		ft_env_addback(&list, temp);
		free(str);
		i++;
	}
	// print_env(temp);
	// print2d(str);
	return (list);
}

void	print_env(t_env *env)
{
	t_env	*temp;

	printf(":(\n");
	temp = env;
	while (temp)
	{
		printf("%s\n", temp->key);
		temp = temp->next;
	}
}

//add new node, put new node in list, delete list
