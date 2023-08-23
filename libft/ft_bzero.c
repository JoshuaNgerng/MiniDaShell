/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:17:39 by mukhairu          #+#    #+#             */
/*   Updated: 2022/10/05 11:42:16 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero( void *str, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*(char *)str = '\0';
		str++;
		i++;
	}
}

//#include <string.h>

/*int	main(void)
{
	char str[] = "This is just a test!";
	printf("Bef: %s\n", str);
	ft_bzero(str + 3, 1);
	printf("Aft: %s\n", &str[3]);
	return (0);
}*/
