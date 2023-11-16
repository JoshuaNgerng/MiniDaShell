/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:53:24 by jngerng           #+#    #+#             */
/*   Updated: 2023/03/15 10:32:58 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 69
# endif

char	*get_next_line(int fd);
char	*ft_sp_strchr(const char *s, int c, int *i);

#endif
