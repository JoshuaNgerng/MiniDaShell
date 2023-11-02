/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:51:35 by mukhairu          #+#    #+#             */
/*   Updated: 2022/10/18 11:36:57 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				len;
	unsigned char	*str;

	str = (unsigned char *)s;
	len = ft_strlen(s);
	while (len >= 0)
	{
		if (str[len] == (unsigned char) c)
			return ((char *)&str[len]);
		len--;
	}
	return (NULL);
}

//#include <string.h>

/*int	main(void)
{
	char str1[20] = "Lim$au ayy";
	char str2[20] = "ayy Limau$";
	printf("str1: %s\nstr2: %s\n", ft_strrchr(str1, '$'), strrchr(str2, '$'));
	return(0);
}*/
