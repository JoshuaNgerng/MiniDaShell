/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 21:59:08 by jngerng           #+#    #+#             */
/*   Updated: 2023/01/05 16:14:39 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

typedef struct s_flags
{
	int	hash_flag;
	int	neg_zero_flag;
	int	plus_sp_flag;
	int	width;
	int	dot;
	int	precision;
}	t_flags;

typedef struct s_int
{
	int		len;
	int		sign;
	char	buffer[11];
}	t_int;

typedef struct s_hex
{
	int		len;
	char	buffer[17];
	char	hex[3];
}	t_hex;

int		ft_printf(const char *format, ...);
int		ft_vfprintf(int fd, const char *format, va_list args);
int		process_format(int fd, const char *format, va_list args, int *index);
int		write_format(int fd, const char format, t_flags mod, va_list args);
int		ft_checkset(char const s, char const *set);
t_flags	get_flags(const char *format, int *index, char *end);
int		ft_sp_atoi(int check, const char *format, int *index);
char	*ft_strcpy(char *dest, const char *src);
int		write_width(int fd, int width, char sp);
int		write_char(int fd, t_flags flag, char c);
int		write_str(int fd, t_flags flag, char *str);
int		ft_put_unsign(unsigned long long u, unsigned int base);
int		get_num(int sign, int input, char *buffer);
int		write_sign_int(int fd, t_flags flag, int input);
int		write_unsign_int(int fd, t_flags flag, int input);
int		process_hex(int fd, t_flags mod, t_hex input);
int		write_hex(int fd, int mode, t_flags mod, int input);
int		write_add(int fd, t_flags mod, void *address);

#endif
