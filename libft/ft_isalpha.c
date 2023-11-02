/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:21:44 by mukhairu          #+#    #+#             */
/*   Updated: 2022/10/04 18:07:38 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (c);
	return (0);
}

/*int	main(void)
{
	int	c1 = 49;
	int	c2 = 80;

	printf("%d\n", ft_isalpha(c1));
	printf("%d\n", ft_isalpha(c2));
	return (0);
}*/
