/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 06:16:50 by jngerng           #+#    #+#             */
/*   Updated: 2023/01/05 16:23:26 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_hex(char *num, char *out, unsigned long long n, int len)
{
	out[len] = '\0';
	if (len == 0)
		return ;
	len --;
	while (len >= 0)
	{
		out[len] = num[n % 16];
		n /= 16;
		len --;
	}
}

int	write_hex(int fd, int mode, t_flags mod, int input)
{
	int		out;
	t_hex	hexa;
	char	*num;

	num = &hexa.buffer[0];
	hexa.len = ft_put_unsign((unsigned int) input, 16);
	if (mode == 0)
	{
		get_hex("0123456789abcdef", num, (unsigned int) input, hexa.len);
		ft_strcpy(&hexa.hex[0], "0x");
	}
	if (mode == 1)
	{
		get_hex("0123456789ABCDEF", num, (unsigned int) input, hexa.len);
		ft_strcpy(&hexa.hex[0], "0X");
	}
	if (input == 0)
	{
		if (mod.dot == 1 && mod.precision == 0)
			hexa.len = 0;
		mod.hash_flag = 0;
	}
	out = process_hex(fd, mod, hexa);
	return (out);
}

int	write_add(int fd, t_flags mod, void *address)
{
	int					out;
	t_hex				hexa;
	char				*num;
	unsigned long long	input;

	num = &hexa.buffer[0];
	input = (unsigned long long) address;
	if (!address || input == 0)
	{
		hexa.len = 1;
		if (mod.dot == 1 && mod.precision == 0)
			hexa.len = 0;
		ft_strcpy(hexa.buffer, "0");
	}
	else
	{
		hexa.len = ft_put_unsign(input, 16);
		get_hex("0123456789abcdef", num, input, hexa.len);
	}
	ft_strcpy(&hexa.hex[0], "0x");
	mod.hash_flag = 1;
	out = process_hex(fd, mod, hexa);
	return (out);
}
