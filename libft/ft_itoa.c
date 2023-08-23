/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:01:55 by mukhairu          #+#    #+#             */
/*   Updated: 2022/10/14 18:31:57 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Return: the string representing the integer. NULL if fails
Allocates (with malloc) and returns a string reresenting the integer received
 as an argument. Negative numbers must be handled
*/
static int	ft_count(long n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*ft_check_num(char *str, long num, int len)
{
	if (num == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	while (num > 0)
	{
		str[len] = '0' + (num % 10);
		num = num / 10;
		len--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	long	num;
	int		n_len;
	char	*str;

	num = n;
	n_len = ft_count(n);
	str = (char *)malloc(sizeof(char) * (n_len + 1));
	if (!str)
		return (NULL);
	str[n_len--] = '\0';
	ft_check_num(str, num, n_len);
	return (str);
}

/*int	main(void)
{
	int	num1 = -14234;
	char *str1;
	str1 = ft_itoa(num1);
	printf("%s", str1);
	free(str1);
}*/
