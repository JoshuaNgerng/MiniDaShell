/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:17:50 by mukhairu          #+#    #+#             */
/*   Updated: 2023/11/12 17:32:14 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_env *list, char *input)
{
	t_env	*temp;
	char	**key;
	int		i;

	temp = list;
	i = 0;
	key = ft_split(input, ' ');
	//to test the characters
	printf("%s=\n", temp->key);
	while (key[i])
	{
		temp = chk_key(temp, key[i]);
		if(!temp)
		{
			temp = list;
			i++;
			continue ;
		}
		printf("Key: %s\n", key[i]);
		temp = list;
		i++;
	}
	free2d(key);
}
