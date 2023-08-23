/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:42:32 by mukhairu          #+#    #+#             */
/*   Updated: 2022/10/13 16:54:38 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*dst_str;
	char	*src_str;

	i = 0;
	if (!dst && !src)
		return (0);
	dst_str = dst;
	src_str = (char *)src;
	while (i < len)
	{
		dst_str[i] = src_str[i];
		i++;
	}
	return (dst_str);
}

/*int	main(void)
{
	char str1[50] = "This is a test";
	char str2[50] = "Completed test";

	printf("Bef: %s\n", str1);
	ft_memcpy(str1, str2, sizeof(str2));
	printf("Aft: %s\n", str1);
	return (0);
}*/
