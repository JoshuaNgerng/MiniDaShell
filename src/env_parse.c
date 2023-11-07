/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:49:54 by mukhairu          #+#    #+#             */
/*   Updated: 2023/11/07 17:50:07 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Test
t_env	*get_env_state(char **env)
{
	int		i;
	// int		j;
	t_env	*temp;
	t_env	*list;
	// char	**str;

	i = 0;
	list = NULL;
	if (!env)
		return (NULL);
	while(env[i])
	{
		// if (chk_dbl(env[i], "="))
		// {
		// 	i++;
		// 	continue ;
		// }
		// str = ft_split(env[i], '=');
		// j = -1;
		// while (str[++j])
		// 	printf("testing j: %d\n", j);
		// if (j > 2)
		// 	printf("testing key j %s\n", str[0]);
		temp = ft_env_new(env[i]);
		// printf("test %s \n", temp->key);
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

	printf(":(\n");
	temp = env;
	while (temp)
	{
		printf("%s=", temp->key);
		printf("%s\n", temp->value);
		temp = temp->next;
	}
}

//add new node, put new node in list, delete list
