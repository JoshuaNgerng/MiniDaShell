/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_hex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 04:12:12 by jngerng           #+#    #+#             */
/*   Updated: 2023/01/05 14:03:36 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	put_hex(int fd, t_flags flag, t_hex input)
{
	int	a;
	int	b;
	int	c;

	a = 0;
	b = 0;
	c = 0;
	if (flag.hash_flag == 1 && flag.neg_zero_flag != 1)
		a = write(fd, input.hex, 2);
	if (a == -1)
		return (-1);
	if (flag.precision > input.len && flag.neg_zero_flag != 1)
		b = write_width(fd, flag.precision - input.len, '0');
	if (b == -1)
		return (-1);
	c = write(fd, input.buffer, input.len);
	if (c == -1)
		return (-1);
	return (a + b + c);
}

int	put_space_hex(int fd, t_flags flag, t_hex input)
{
	int	a;
	int	b;
	int	c;

	a = 0;
	b = 0;
	c = 0;
	if (flag.precision > 0 && flag.precision < input.len)
		a = write_width(fd, flag.width - input.len, ' ');
	if (flag.precision >= input.len)
		a = write_width(fd, flag.width - flag.precision, ' ');
	if (flag.hash_flag == 1)
		b = write(fd, input.hex, 2);
	if (flag.precision > input.len)
		c = write_width(fd, flag.precision - input.len, '0');
	if (flag.precision == 0 && flag.width > input.len)
		c = write_width(fd, flag.width - input.len, '0');
	if (a == -1 || b == -1 || c == -1)
		return (-1);
	return (a + b + c);
}

int	process_hex(int fd, t_flags mod, t_hex input)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	if (mod.hash_flag == 1)
		mod.width -= 2;
	if (mod.neg_zero_flag == 2)
		a = put_hex(fd, mod, input);
	if (mod.neg_zero_flag != 1)
	{
		if (mod.precision < input.len)
			b = write_width(fd, mod.width - input.len, ' ');
		else
			b = write_width(fd, mod.width - mod.precision, ' ');
	}
	if (mod.neg_zero_flag == 1)
		b = put_space_hex(fd, mod, input);
	if (mod.neg_zero_flag < 2)
		a = put_hex(fd, mod, input);
	if (a == -1 || b == -1)
		return (-1);
	return (a + b);
}
