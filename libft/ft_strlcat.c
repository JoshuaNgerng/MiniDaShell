/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:42:50 by mukhairu          #+#    #+#             */
/*   Updated: 2022/10/13 18:51:28 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	total;

	i = 0;
	j = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	if (dstsize > ft_strlen(dst))
		total = ft_strlen(src) + ft_strlen(dst);
	else
	{
		total = ft_strlen(src) + dstsize;
		return (total);
	}
	while (dst[i] != '\0')
		i++;
	while (src[j] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	return (total);
}

// int	main(void)
// {
// 	char str1[50] = "This is just a test";
// 	const char str2[] = "Test complete";
// 	printf("%zu", ft_strlcat(str1, str2, 2));
// 	return (0);
// }
