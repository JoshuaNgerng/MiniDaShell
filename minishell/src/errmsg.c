/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errmsg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:31:48 by jngerng           #+#    #+#             */
/*   Updated: 2023/08/18 17:31:48 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
exist cause norminette is a btch
*/
void	*n(void *a, void *b)
{
	(void)a;
	(void)b;
	return (NULL);
}

/*
contains all fixed errmsg
*/
void	*errmsg(int	e)
{
	if (e == 0)
		write(2, "Error\n", 6);
	return (NULL);
}

/*
contains all errmsg with errno msg
char *msg is special msg NULL to skip
err is the errno 
*/

void	*errmsg_errno(int e)
{
	char	*ptr;
	
	ptr = strerror(errno);
	if (e == 1)
		write(2, "fork failed: ", 13);
	if (e == 2)
		write(2, "cannot make pipes: ", 19);
	if (e == 3)
		write(2, "here_doc : ", 10);
	if (e == 4)
		write(2, "write to pipe failed: ", 22);
	if (e == 5)
		write(2, "dup2 failed: ", 13);
	write(2, ptr, ft_strlen(ptr));
	write(2, "\n", 1);
	errno = 0;
	return (NULL);
}

void	*sp_errmsg(int e, char *msg)
{
	char	*ptr;
	
	ptr = strerror(errno);
	if (e == 1)
		write(2, "failed to get input: ", 21);
	if (e == 2)
		write(2, "initialsation failed: ", 22);
	if (msg)
		write(2, msg, ft_strlen(msg));
	if (e == 3)
		write(2, ": ", 2);
	write(2, ptr, ft_strlen(ptr));
	write(2, "\n", 1);
	errno = 0;
	return (NULL);
}
