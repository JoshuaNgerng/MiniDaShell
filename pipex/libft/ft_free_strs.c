/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeptrptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:04:41 by jngerng           #+#    #+#             */
/*   Updated: 2023/05/15 09:04:41 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_free_strs(char **src)
{
	unsigned int	i;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i])
	{
		free(src[i]);
		src[i] = NULL;
		i ++;
	}
	free(src);
	src = NULL;
	return (src);
}
