/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:48:49 by mukhairu          #+#    #+#             */
/*   Updated: 2022/10/13 20:27:37 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	l_len;

	i = 0;
	l_len = ft_strlen(to_find);
	if (!str && len == 0)
		return (0);
	if (to_find[i] == '\0')
		return ((char *)str);
	while (str[i] != '\0' && i < len)
	{
		j = 0;
		while (str[i + j] != '\0' && str[i + j] == to_find[j]
			&& to_find[j] != '\0' && (i + j < len))
		{
			j++;
			if (j == l_len)
				return ((char *)str + i);
		}
		i++;
	}
	return (0);
}

// char	*ft_strnstr(const char *str, const char *to_find, size_t len)
// {
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	if (to_find[i] == '\0')
// 		return ((char *)str);
// 	while (str[i] != '\0' && i < len)
// 	{
// 		j = 0;
// 		while (to_find[j] != '\0' && str[i + j] == to_find[j]
// 			&& (i + j < len))
// 		{
// 			j++;
// 			if (to_find[j] == '\0')
// 				return ((char *)&str[i]);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

/*#include <string.h>

int	main(void)
{
	char str1[] = "Can I find the words?";
	//char str2[] = "find";

	printf("%s\n", ft_strnstr(str1, "\0", sizeof(str1)));
	printf("%s\n", strnstr(str1, "\0", sizeof(str1)));
	return (0);
}*/
