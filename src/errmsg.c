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

void	*sp_errmsg(int	e, char *msg, int err)
{
	char	*ptr;
	
	ptr = strerror(err);
	if (e == 0)
		write(2, "Failed to get input: ", 21);
	if (e == 1)
		write(2, "Initialsation failed: ", 22);
	if (msg)
		write(2, msg, ft_strlen(msg));
	write(2, ptr, ft_strlen(ptr));
	return (NULL);
}