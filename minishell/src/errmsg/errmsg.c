/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errmsg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:43:01 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/01 08:30:16 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	errmsg_name(char *name_)
{
	static int	len;
	static char	*name;

	if (!name)
	{
		name = name_;
		len = ft_strlen(name);
		return ;
	}
	write(2, name, len);
	write(2, ": ", 2);
}

void	*errmsg(int e)
{
	errmsg_name(NULL);
	if (e == 1)
		write(2, "syntax error have non-ascii char\n", 33);
	else if (e == 2)
		write(2, "syntax error: unexpected end of file\n", 37);
	else if (e == 3)
		write(2, "warning: here-document delimited by end-of-file\n", 48);
	return (NULL);
}

void	*errmsg_var(int e, char *msg, int len)
{
	errmsg_name(NULL);
	if (!len)
		len = ft_strlen(msg);
	if (e == 1)
		write(2, "syntax error near unexpected token `", 36);
	if (e == 2)
		write(2, "unexpected EOF while looking for matching `", 43);
	if (msg)
		write(2, msg, len);
	if (e != 3)
		write(2, "'\n", 2);
	if (e == 3)
		write(2, ": command not found\n", 20);
	return (NULL);
}

void	*errmsg_token(int token)
{
	char	**s;
	int		i;
	int		*array;
	int		index;
	int		check;

	s = (char *[9]){"<<", "<", ">", ">>", "|", "||", "&&", "(", ")"};
	array = (int []){2, 1, 1, 2, 1, 2, 2, 1, 1};
	index = 0;
	check = 0;
	if (!token || token < 0)
		return (NULL);
	while (!check)
	{
		check = (token & (1 << index));
		index ++;
	}
	i = array[index - 1];
	return (errmsg_var(1, s[index -1], i));
}

void	*sp_errmsg(int e, char *msg)
{
	char	*ptr;

	errmsg_name(NULL);
	if (msg)
		write(2, msg, ft_strlen(msg));
	if (e == 3)
		write(2, ": ", 2);
	if (errno > 0)
	{
		ptr = strerror(errno);
		write(2, ptr, ft_strlen(ptr));
	}
	write(2, "\n", 1);
	errno = 0;
	return (NULL);
}
