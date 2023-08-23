/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:15:16 by mukhairu          #+#    #+#             */
/*   Updated: 2022/10/06 18:32:57 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*target;
	int		i;
	char	*str1;

	i = 0;
	str1 = (char *)s1;
	len = ft_strlen(str1) + 1;
	target = malloc(sizeof(char) * len);
	if (target == NULL)
		return (NULL);
	while (str1[i] != '\0')
	{
		target[i] = str1[i];
		i++;
	}
	target[i] = '\0';
	return (target);
}
