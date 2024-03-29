/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:47:06 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/01 03:59:06 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_checkset(char const s, char const *set)
{
	while (*set)
	{
		if (*set == s)
			return (1);
		set ++;
	}
	return (0);
}

int	pass_space(char *input, int start)
{
	int	end;

	end = start;
	while (input[end] && input[end] == ' ')
		end ++;
	return (end);
}

int	int_strchr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i ++;
	if (s[i] != c)
		return (-1);
	return (i);
}

int	read_quo(char ref, int quo)
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

int	int_strcpy(char *dst, int index, const char *src)
{
	int	j;

	j = -1;
	while (src[++ j])
		dst[index ++] = src[j];
	return (index);
}
