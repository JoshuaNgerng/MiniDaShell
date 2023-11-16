/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 22:00:51 by jngerng           #+#    #+#             */
/*   Updated: 2023/05/09 14:43:48 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flags	get_flags(const char *format, int *index, char *end)
{
	t_flags	out;

	*index = 0;
	out = (struct s_flags){0, 0, 0, 0, 0, 0};
	while (ft_checkset(format[++ (*index)], "-+0 #") == 1 && format[*index])
	{
		if (format[*index] == '-')
			out.neg_zero_flag = 2;
		if (format[*index] == '+')
			out.plus_sp_flag = 2;
		if (format[*index] == ' ' && out.plus_sp_flag == 0)
			out.plus_sp_flag = 1;
		if (format[*index] == '0' && out.neg_zero_flag == 0)
			out.neg_zero_flag = 1;
		if (format[*index] == '#')
			out.hash_flag = 1;
	}
	out.width = ft_sp_atoi(0, format, index);
	if (format[*index] == '.')
	{
		out.dot = 1;
		out.precision = ft_sp_atoi(1, format, index);
	}
	*end = format[*index];
	return (out);
}

int	write_format(int fd, const char format, t_flags mod, va_list args)
{
	int	out;

	out = 0;
	if (format == 'c')
		out = write_char(fd, mod, va_arg(args, int));
	else if (format == 's')
		out = write_str(fd, mod, va_arg(args, char *));
	else if (format == 'p')
		out = write_add(fd, mod, va_arg(args, void *));
	else if (format == 'd' || format == 'i')
		out = write_sign_int(fd, mod, va_arg(args, int));
	else if (format == 'u')
		out = write_unsign_int(fd, mod, va_arg(args, int));
	else if (format == 'x')
		out = write_hex(fd, 0, mod, va_arg(args, int));
	else if (format == 'X')
		out = write_hex(fd, 1, mod, va_arg(args, int));
	if (out == -1)
		return (-1);
	return (out);
}

int	process_format(int fd, const char *format, va_list args, int *index)
{
	int		l;
	char	specifer;
	t_flags	mod;

	mod = get_flags(format, index, &specifer);
	if (mod.dot == 1 && mod.neg_zero_flag == 1)
		mod.neg_zero_flag = 0;
	if (ft_checkset(specifer, "cspdiuxX%") == 0)
		return (0);
	if (specifer == '%')
		l = write_char(fd, mod, '%');
	else
		l = write_format(fd, specifer, mod, args);
	if (l == -1)
		return (-1);
	return (l);
}

int	ft_vfprintf(int fd, const char *format, va_list args)
{
	int	i;
	int	l;
	int	j;
	int	out;

	i = -1;
	j = 0;
	out = 0;
	while (format[++ i])
	{
		if (format[i] == '%')
		{
			l = process_format(fd, &format[i], args, &j);
			i += j;
			if (!format[i])
				break ;
		}
		else
			l = write(fd, &format[i], 1);
		if (l == -1)
			return (-1);
		out += l;
	}
	return (out);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		output;

	va_start(args, format);
	output = ft_vfprintf(1, format, args);
	va_end(args);
	return (output);
}
