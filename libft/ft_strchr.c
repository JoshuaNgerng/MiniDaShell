/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:07:23 by mukhairu          #+#    #+#             */
/*   Updated: 2022/10/17 21:10:35 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	int				len;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	len = ft_strlen(s);
	while (i < len)
	{
		if (str[i] == (unsigned char) c)
			return ((char *)&str[i]);
		i++;
	}
	if (c == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

/*#include <string.h>

int	main(void)
{
	char str1[20] = "Limau ayy$";
	char str2[20] = "ayy Limau$";
	printf("str1: %s\nstr2: %s\n", ft_strchr(str1, '\0'), strchr(str2, '\0'));
	return(0);
}*/
