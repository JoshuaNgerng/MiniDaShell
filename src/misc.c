/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:56:31 by mukhairu          #+#    #+#             */
/*   Updated: 2023/11/15 15:23:43 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	chk_stx(char *str, int vld)
{
	char	*chk_str;
	int i;

	chk_str = str;
	i = 1;
	if (!ft_isalpha(str[0]))
	{
		printf("Error: %s: invalid syntax\n", str);
		return (0);
	}
	while (chk_str[i] && chk_str[i] != '=')
	{
		if (!ft_isalnum(chk_str[i]) && chk_str[i] != '_')
		{
			printf("Error: %s: invalid syntax\n", str);
			return (0);
		}
		i++;
	}
	if (chk_str[i] != '=' && vld == 1)
	{
		printf("Error: %s: invalid syntax\n", str);
			return (0);
	}
	return (1);
}

void	print_export(t_env *list)
{
	t_env	*temp;

	temp = list;
	while(temp)
	{
		printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
		temp = temp->next;
	}
}

int	chk_dbl(char *str, char c)
{
	int	i;
	int	cnt;

	i = -1;
	cnt = 0;
	while (str[i++])
	{
		if (str[i] == c)
			cnt++;
	}
	if (cnt > 1)
		return (1);
	return (0);
}
