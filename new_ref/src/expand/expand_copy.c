/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:52:18 by jngerng           #+#    #+#             */
/*   Updated: 2024/01/31 09:04:28 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	copy_expand_env(char *dst, t_token *list, int quo)
{
	int	i;

	if (!list->token)
		return (0);
	i = -1;
	while (list->token[++ i])
	{
		if (list->token[i] == ' ' && quo)
		{
			dst[i] = -32;
			continue ;
		}
		if (list->token[i] == '\n')
		{
			dst[i] = ' ';
			continue ;
		}
		dst[i] = list->token[i];
	}
	return (i);
}

static int	check_src_copy(char *dst, char *src, int *index, int *quo)
{
	int	check;

	check = 0;
	if (src[0] < 0)
		return (1);
	if (src[0] == '$' && src[1] && !ft_checkset(src[1], "'\" "))
	{
		if (!(*quo) || *quo == '"')
			return (1);
	}
	if (src[0] == '\'' || src[0] == '"')
	{
		check = 1;
		*quo = read_quo(src[0], *quo);
		if (*quo && *quo != src[0])
			check = 0;
	}
	if (check)
		return (0);
	if (src[0] == ' ' && quo)
		dst[*index] = -32;
	else
		dst[*index] = src[0];
	(*index)++;
	return (0);
}

void	copy_expand(char *dst, char *src, t_token *list, t_token *list_malloc)
{
	int	i;
	int	j;
	int	quo;

	i = -1;
	j = 0;
	quo = 0;
	// printf("test list\n");
	// dev_print_tokens(list);
	// printf("test list_malloc\n");
	// dev_print_tokens(list_malloc);
	while (src[++ i])
	{
		if (!check_src_copy(dst, &src[i], &j, &quo))
			continue ;
		if (src[i] < 0)
		{
			// printf("testing list_malloc %p\n", list_malloc);
			j += copy_expand_env(&dst[j], list_malloc, quo);
			i += list_malloc->type;
			list_malloc = list_malloc->next;
		}
		else
		{
			j += copy_expand_env(&dst[j], list, quo);
			i += list->type;
			list = list->next;
		}
	}
	dst[j] = '\0';
}
