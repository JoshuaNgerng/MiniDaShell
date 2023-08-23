/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:57:23 by mukhairu          #+#    #+#             */
/*   Updated: 2022/10/04 18:13:02 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| ((c >= '0' && c <= '9')))
		return (c);
	return (0);
}

/*int	main(void)
{
	int	c1 = 33;
	int	c2 = 80;

	printf("%d\n", ft_isalnum(c1));
	printf("%d\n", ft_isalnum(c2));
	return (0);
}*/
