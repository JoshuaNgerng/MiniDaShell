/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:36:56 by mukhairu          #+#    #+#             */
/*   Updated: 2022/10/13 17:00:51 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*((unsigned char *)str + i) = (unsigned char)c;
		i++;
	}
	return (str);
}

//#include <string.h>

/*int	main(void)
{
	char str[] = "This is just a test!";
	printf("Bef: %s\n", str + 3);
	ft_memset(str + 3, '?', 5);
	printf("Aft: %s\n", str);
	return (0);
}*/
