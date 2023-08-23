/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 19:35:30 by mukhairu          #+#    #+#             */
/*   Updated: 2022/10/05 19:38:47 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
	return (c);
}

/*#include <ctype.h>

int	main(void)
{
	char c1 = 'A';
	char c2 = 'Y';

	//ft_toupper(c1);
	//toupper(c2);
	printf("%c, %c", ft_tolower(c1), tolower(c2));
	return (0);
}*/
