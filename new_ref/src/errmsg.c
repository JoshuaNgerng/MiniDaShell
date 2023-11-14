/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errmsg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:05:18 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/10 23:37:42 by jngerng          ###   ########.fr       */
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

void	*errmsg_token(char *input)
{
	if (input[0] == input[1])
		errmsg_var(1, input, 2);
	else
		errmsg_var(1, input, 1);
	return (NULL);
}

void	*errmsg_errno(int e)
{
	char	ptr;

	if (e == 1)
		write(2, "Cannot access enviroment variable: ", 35);
	else if (e == 2)
		write(2, "Cannot receive input from user: ", 32);
	else if (e == 3)
		write(2, "Cannot get directory path: ", 27);
	else if (e == 4)
		write(2, "t_block (malloc): ", 18);
	else if (e == 5)
		write(2, "t_token (malloc): ", 18);
	ptr = strerror(errno);
	if (ptr)
		write(2, ptr, ft_strlen(ptr));
	write(2, "\n", 1);
	errno = 0;
	return (NULL);
}

void	handle_error(t_shell *s, int ext_code)
{
	s->status = ext_code;
	free_tokens(s->input);
	s->input = 1;
}