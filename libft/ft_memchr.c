/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:28:39 by mukhairu          #+#    #+#             */
/*   Updated: 2022/10/13 16:49:22 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}

/*#include <string.h>

int	main(void)
{
	char str1[20] = "Limau $ayy";
	char str2[20] = "ayy $Limau";
	printf("str1: %s\nstr2: %s\n", ft_memchr(str1, '$', 10), memchr(str2, '$',2));
	return(0);
}*/
