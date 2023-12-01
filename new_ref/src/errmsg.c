/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errmsg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:05:18 by jngerng           #+#    #+#             */
/*   Updated: 2023/12/01 14:31:03 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*errmsg(int e)
{
	if (e == 1)
		write(2, "syntax error have non-ascii char\n", 33);
	if (e == 2)
		write(2, "syntax error: unexpected end of file", 36);
	return (NULL);
}

void	*errmsg_var(int e, char *msg, int len)
{
	if (!len)
		len = ft_strlen(msg);
	if (e == 1)
		write(2, "syntax error near unexpected token `", 36);
	if (e == 2)
		write(2, "unexpected EOF while looking for matching `", 43);
	if (msg)
		write(2, msg, len);
	write(2, "'\n", 2);
	return (NULL);
}

void	*errmsg_token(int token)
{
	char	**s;
	int		*i;
	int		index;
	int		check;

	s = (char *[9]){"<<", "<", ">", ">>", "|", "||", "&&", "(", ")"};
	i = (int []){2, 1, 1, 2, 1, 2, 2, 1, 1};
	index = 0;
	check = 0;
	if (!token || token < 0)
		return (NULL);
	while (!check)
	{
		check = (token & (1 << index));
		index ++;
	}
	return (errmsg_var(1, s[index -1], index - 1));
}

void	*errmsg_errno(int e)
{
	char	*ptr;

	if (e == 1)
		write(2, "Cannot access enviroment variable: ", 35);
	else if (e == 2)
		write(2, "Cannot receive input from user: ", 32);
	else if (e == 3)
		write(2, "Cannot get directory path: ", 27);
	else if (e == 4)
		write(2, "t_token (malloc): ", 18);
	else if (e == 5)
		write(2, "t_proc (malloc): ", 17);
	else if (e == 6)
		write(2, "t_buffer (malloc): ", 19);
	else if (e == 7)
		write(2, "subshell (fork): ", 19);
	else if (e == 8)
		write(2, "t_env (malloc): ", 16);
	else if (e == 9)
		write(2, "dup2: ", 6);
	else if (e == 10)
		write(2, "find_cmd (malloc): ", 19);
	else if (e == 11)
		write(2, "get_cmd_array (malloc): ", 24);
	if (errno > 0)
	{
		ptr = strerror(errno);
		write(2, ptr, ft_strlen(ptr));
	}
	write(2, "\n", 1);
	errno = 0;
	return (NULL);
}

void	*sp_errmsg(int e, char *msg)
{
	char	*ptr;

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
