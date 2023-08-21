/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 07:19:54 by jngerng           #+#    #+#             */
/*   Updated: 2023/05/15 07:19:54 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

char	*ft_strndup(const char *src, unsigned int n)
{
	unsigned int	i;
	char			*out;

	out = (char *) malloc ((n + 1) * sizeof(char));
	if (!out)
		return (NULL);
	i = 0;
	while (i < n && src[i])
	{
		out[i] = (char)src[i];
		i ++;
	}
	out[i] = '\0';
	return (out);
}
