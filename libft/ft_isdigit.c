/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:43:02 by mukhairu          #+#    #+#             */
/*   Updated: 2023/04/06 13:14:58 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (c);
	return (0);
}

/*int	main(void)
{
	int	c1 = 49;
	int	c2 = 80;

	printf("%d\n", ft_isdigit(c1));
	printf("%d\n", ft_isdigit(c2));
	return (0);
}*/
