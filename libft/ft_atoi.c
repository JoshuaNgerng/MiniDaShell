/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:30:54 by mukhairu          #+#    #+#             */
/*   Updated: 2022/10/06 16:45:25 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		res;
	int		sign;
	int		i;
	char	*pstr;

	res = 0;
	sign = 1;
	i = 0;
	pstr = (char *)str;
	while (pstr[i] == 32 || (pstr[i] >= 9 && pstr[i] <= 13))
		i++;
	if (pstr[i] == '-' || pstr[i] == '+')
	{
		if (pstr[i] == '-')
			sign = -(sign);
		i++;
	}
	while (pstr[i] >= '0' && pstr[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}
