/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:24:15 by mukhairu          #+#    #+#             */
/*   Updated: 2022/10/04 17:59:09 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (c);
	return (0);
}

/*int	main(void)
{
	int	c1 = 40;
	int	c2 = 8;

	printf("%d\n", ft_isprint(c1));
	printf("%d\n", ft_isprint(c2));
	return (0);
}*/
