/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:47:24 by mukhairu          #+#    #+#             */
/*   Updated: 2022/10/18 12:45:40 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Allocates (with malloc) and returns a substring from the string 's'
The substring begins at index 'start'and is of maximum size 'len'
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	new_len;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	new_len = ft_strlen(s + start);
	if (len > new_len)
		len = new_len;
	ptr = ft_calloc((len + 1), sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s += start, len + 1);
	return (ptr);
}

/*int	main(void)
{
	char str[50] = "What'cha say?";
	char	*p;
	int	pos = 3;
	int	length = 5;

	p = ft_substr(str, pos, 5);
	printf("%s\n", p);
	free(p);
	return (0);
}*/
