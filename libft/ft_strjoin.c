/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:09:24 by mukhairu          #+#    #+#             */
/*   Updated: 2023/06/23 19:12:09 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Allocates (with malloc) and returns a new string, which is the result
//of the concatenation of 's1' and 's2'
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		cat;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(ft_strlen(s1) * sizeof(char)
			+ ft_strlen(s2) * sizeof(char) + 1);
	if (!str)
		return (NULL);
	i = 0;
	cat = 0;
	while (s1[i])
	{
		str[cat++] = s1[i++];
	}
	i = 0;
	while (s2[i])
	{
		str[cat++] = s2[i++];
	}
	str[cat] = '\0';
	return (str);
}
