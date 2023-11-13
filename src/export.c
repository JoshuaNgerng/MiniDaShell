/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:35:06 by mukhairu          #+#    #+#             */
/*   Updated: 2023/11/13 19:27:37 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*chk_key(t_env *list, char *str)
{
	t_env	*temp;
	char	*chk_str;
	int i;

	temp = list;
	chk_str = str;
	i = 0;
	while (chk_str[i] && chk_str[i] != '=')
	{
		if (ft_isalpha(chk_str[i]) == 0 && chk_str[i] != '_')
		{
			printf("Error: %s: invalid identifier\n", str);
			return (NULL);
		}
		i++;
	}
	while (temp)
	{
		// printf("test: %s\n", temp->key);
		if (!ft_strncmp(temp->key, str, ft_strlen(str)))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
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
	if (!str[i])
		val =  ft_strdup("");
	else
		val = ft_strdup(&str[i + 1]);
	temp = chk_key(list, key);
	if (!temp)
	{
		temp = ft_env_new(str);
		ft_env_addback(&list, temp);
		free(key);
		free(val);
		return ;
	}
	free(temp->value);
	temp->value = val;
	free(key);
}
