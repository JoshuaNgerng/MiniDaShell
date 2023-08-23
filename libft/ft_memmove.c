/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:37:38 by mukhairu          #+#    #+#             */
/*   Updated: 2022/10/12 17:17:39 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (dst == src)
		return (dst);
	i = 0;
	if (dst < src)
	{
		while (i < len)
		{
			*((char *)dst + i) = *((char *)src + i);
			i++;
		}
	}
	else
	{
		while (len--)
		{
			*((char *)dst + len) = *((char *)src + len);
		}
	}
	return (dst);
}

/*#include <string.h>

int	main(void)
{
	char str1[] = "Testing the code 1";
	//char str2[] = "Result";
	ft_memmove(str1 + 9, str1 + 3, 10);
	printf("%s", str1);
	return (0);
}*/
