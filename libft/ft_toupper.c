/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 19:19:16 by mukhairu          #+#    #+#             */
/*   Updated: 2022/10/05 19:33:24 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c = c - 32;
	return (c);
}

/*#include <ctype.h>

int	main(void)
{
	char c1 = 'a';
	char c2 = 'y';

	//ft_toupper(c1);
	//toupper(c2);
	printf("%c, %c", ft_toupper(c1), toupper(c2));
	return (0);
}*/
