/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_char_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 09:15:49 by jngerng           #+#    #+#             */
/*   Updated: 2023/01/05 16:22:59 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i ++;
	return (i);
}

static int	write_char_str_wid(int fd, t_flags flag, int len)
{
	int		out;
	char	sp;

	out = 0;
	if (flag.neg_zero_flag == 1)
		sp = '0';
	else
		sp = ' ';
	out = write_width(fd, flag.width - len, sp);
	return (out);
}

int	write_char(int fd, t_flags flag, char c)
{
	int		l;
	int		p;

	l = 0;
	p = 0;
	if (flag.neg_zero_flag == 2)
		l = write(fd, &c, 1);
	if (flag.width > 1)
		p = write_char_str_wid(fd, flag, 1);
	if (p == -1)
		return (-1);
	if (flag.neg_zero_flag < 2)
		l = write(fd, &c, 1);
	if (l == -1)
		return (-1);
	return (l + p);
}

int	write_str(int fd, t_flags flag, char *str)
{
	int		l;
	int		p;
	int		len;
	char	buffer[7];

	l = 0;
	p = 0;
	if (!str)
		str = ft_strcpy(&buffer[0], "(null)");
	len = ft_strlen(str);
	if (len > flag.precision && flag.dot != 0)
		len = flag.precision;
	if (flag.neg_zero_flag == 2)
		l = write(fd, str, len);
	if (flag.width - len > 0)
		p = write_char_str_wid(fd, flag, len);
	if (p == -1)
		return (-1);
	if (flag.neg_zero_flag < 2)
		l = write(fd, str, len);
	if (l == -1)
		return (-1);
	return (l + p);
}
