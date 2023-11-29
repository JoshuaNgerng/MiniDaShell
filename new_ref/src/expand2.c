/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:12:07 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/29 19:46:18 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_quo(char ref, int quo)
{
	if (quo)
	{
		if (ref == quo)
			quo = 0;
	}
	else
		quo = ref;
	return (quo);
}

int	search_expand(char *str, t_token **list, int *len, int *check)
{
	int		i;
	int		l;
	int		quo;
	int		space;
	t_ptr	buffer;

	space = 0;
	i = -1;
	l = 0;
	buffer = (t_ptr){0, 0};
	while (str[++ i])
	{
		if (str[i] == '\'' || str[i] == '"')
			quo = read_quo(str[i], quo);
		else if (str[i] == '$' && (!quo || quo == '"'))
		{
			if ()
				return (1);
		}
		else
			l ++;
	}
	*list = buffer.head;
	if (check)
		*check = space;
	*len = l;
	return (0);
}

static int	copy_expand_var(char *dst, int *j, t_env **list, char *src)
{
	int	i;

	return (i);
}

void	copy_expand(char *dst, t_token *list, char *src)
{
	int	i;
	int	j;
	int	quo;

	i = -1;
	j = 0;
	quo = 0;
	while (src[++ i])
	{
		if (src[i] == '\'' || src[i] == '"')
			quo = read_quo(src[i], quo);
		if (src[i] == '$' && (!quo || quo == '"'))
			i += copy_expand_var(dst, &j, &list, &src[i]);
		else
			dst[j ++] = src[i];
	}
	dst[j] = '\0';
}
