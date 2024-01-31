/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:51:45 by jngerng           #+#    #+#             */
/*   Updated: 2022/10/26 16:39:39 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
// #include <stdio.h>

static int	get_size(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		i = 1;
		n = -n;
	}
	if (n >= 10)
	{
		i += get_size(n / 10);
		n %= 10;
	}
	if (n < 10)
		i += 1;
	return (i);
}

static char	*ft_strcpy(char *dest, char *src)
{
	char	*buffer;

	buffer = dest;
	while (*src)
	{
		*buffer = *src;
		buffer ++;
		src ++;
	}
	*buffer = '\0';
	return (dest);
}

static char	*get_number(char *input, int n, int len)
{
	int	sign;

	sign = 0;
	if (n == -2147483648)
		return (ft_strcpy(input, "-2147483648"));
	input[len --] = '\0';
	if (n == 0)
	{
		input[0] = '0';
		return (input);
	}
	if (n < 0)
	{
		n = -n;
		sign = 1;
	}
	while (n > 0)
	{
		input[len] = n % 10 + '0';
		n /= 10;
		len --;
	}
	if (sign)
		input[0] = '-';
	return (input);
}

char	*ft_itoa(int n)
{
	int		s;
	char	*ptr;

	s = get_size(n);
	ptr = (char *)malloc((s + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ptr = get_number(ptr, n, s);
	return (ptr);
}

// #include <stdio.h>
// int	main(void)
// {
// 	int	n = 0;
// 	char	*s = ft_itoa(n);
// 	printf("test fin:%s\n", s);
// 	free(s);
// 	return (0);
// }