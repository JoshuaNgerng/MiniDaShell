/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 09:30:15 by jngerng           #+#    #+#             */
/*   Updated: 2022/12/12 09:30:15 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_put_nbr(int nb)
{
	int	t;

	t = 0;
	if (nb == -2147483648)
		return (10);
	if (nb < 0)
		nb = -nb;
	if (nb >= 10)
	{
		t += ft_put_nbr(nb / 10);
		nb %= 10;
	}
	if (nb < 10)
		t ++;
	return (t);
}

static void	get_unsign_num(char *out, unsigned int n, int len)
{
	out[len] = '\0';
	if (len == 0)
		return ;
	len --;
	while (len >= 0)
	{
		out[len] = n % 10 + '0';
		n /= 10;
		len --;
	}
}

static char	*get_sign_num(char *out, int n, int len)
{
	if (n == -2147483648)
		return (ft_strcpy(out, "2147483648"));
	out[len] = '\0';
	if (n < 0)
		n = -n;
	if (len == 0)
		return (out);
	len --;
	while (len >= 0)
	{
		out[len] = n % 10 + '0';
		n /= 10;
		len --;
	}
	return (out);
}

int	get_num(int sign, int input, char *buffer)
{
	int	len;

	len = 0;
	if (sign == 0)
	{
		len = ft_put_unsign((unsigned int)input, 10);
		get_unsign_num(buffer, input, len);
	}
	if (sign == 1)
	{
		len = ft_put_nbr(input);
		get_sign_num(buffer, input, len);
	}
	return (len);
}

int	ft_put_unsign(unsigned long long u, unsigned int base)
{
	int	out;

	out = 0;
	if (u >= base)
	{
		out += ft_put_unsign(u / base, base);
		u %= 10;
	}
	if (u < base)
		out ++;
	return (out);
}
