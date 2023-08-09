/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 03:45:16 by jngerng           #+#    #+#             */
/*   Updated: 2023/01/05 14:31:22 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_sp_atoi(int check, const char *format, int *index)
{
	int	out;

	out = 0;
	if (check == 1 && format[*index])
		(*index)++;
	while (format[*index] >= '0' && format[*index] <= '9' && format[*index])
	{
		out = out * 10 + format[*index] - '0';
		(*index)++;
	}
	return (out);
}

int	ft_checkset(char const s, char const *set)
{
	while (*set)
	{
		if (*set == s)
			return (1);
		set ++;
	}
	return (0);
}

char	*ft_strcpy(char *dest, const char *src)
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

int	write_width(int fd, int width, char sp)
{
	int	i;
	int	l;
	int	out;

	out = 0;
	i = -1;
	while (++ i < width)
	{
		l = write(fd, &sp, 1);
		if (l == -1)
			return (-1);
		out += l;
	}
	return (out);
}
