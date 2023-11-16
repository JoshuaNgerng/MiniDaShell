/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 09:34:31 by jngerng           #+#    #+#             */
/*   Updated: 2023/05/09 14:56:33 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	write_num(int fd, t_int input, t_flags flag)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	if (flag.dot != 0 && flag.precision - input.len > 0)
		a = write_width(fd, flag.precision - input.len, '0');
	if (flag.neg_zero_flag == 1 && flag.width > input.len + input.sign)
		a = write_width(fd, flag.width - input.len - input.sign, '0');
	if (a == -1)
		return (-1);
	b = write(fd, input.buffer, input.len);
	if (b == -1)
		return (-1);
	return (a + b);
}

static int	write_sign_num(int fd, int num, t_int input, t_flags flag)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	if (num < 0 && input.sign == 1)
		a = write(fd, "-", 1);
	if (num >= 0 && flag.plus_sp_flag == 1)
		a = write(fd, " ", 1);
	if (num >= 0 && flag.plus_sp_flag == 2)
		a = write(fd, "+", 1);
	b = write_num(fd, input, flag);
	if (a == -1 || b == -1)
		return (-1);
	return (a + b);
}

static t_int	process_int(t_int num, t_flags flag, int input)
{
	if (flag.plus_sp_flag > 0 || input < 0)
		num.sign = 1;
	if (flag.precision == 0 && flag.dot == 1 && input == 0)
		num.len = 0;
	return (num);
}

int	write_sign_int(int fd, t_flags flag, int input)
{
	t_int	num;
	int		space;
	int		a;
	int		b;

	a = 0;
	b = 0;
	num.sign = 0;
	num.len = get_num(1, input, &num.buffer[0]);
	num = process_int(num, flag, input);
	if (flag.precision > num.len)
		space = flag.precision;
	else
		space = num.len;
	if (flag.neg_zero_flag == 2)
		a = write_sign_num(fd, input, num, flag);
	if (flag.width > space && flag.neg_zero_flag != 1)
		b = write_width(fd, flag.width - space - num.sign, ' ');
	if (flag.neg_zero_flag < 2)
		a = write_sign_num(fd, input, num, flag);
	if (a == -1 || b == -1)
		return (-1);
	return (a + b);
}

int	write_unsign_int(int fd, t_flags flag, int input)
{
	t_int	num;
	int		space;
	int		a;
	int		b;

	a = 0;
	b = 0;
	num.sign = 0;
	num.len = get_num(0, input, &num.buffer[0]);
	if (flag.precision == 0 && flag.dot == 1 && input == 0)
		num.len = 0;
	if (flag.precision > num.len)
		space = flag.precision;
	else
		space = num.len + num.sign;
	if (flag.neg_zero_flag == 2)
		a = write_num(fd, num, flag);
	if (flag.width > space && flag.neg_zero_flag != 1)
		b = write_width(fd, flag.width - space, ' ');
	if (flag.neg_zero_flag < 2)
		a = write_num(fd, num, flag);
	if (a == -1 || b == -1)
		return (-1);
	return (a + b);
}
