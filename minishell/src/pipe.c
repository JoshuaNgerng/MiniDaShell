/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:13:27 by jngerng           #+#    #+#             */
/*   Updated: 2023/09/14 16:23:04 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	clean_all_pipes(int *pfd, int lim)
{
	int	i;
	int	out;

	i = -1;
	out = 0;
	while (++ i < lim)
	{
		if (close(pfd[i * 2]) || close(pfd[i * 2 + 1]))
		{
			errmsg_errno(2);
			out = 1;
		}
	}
	return (out);
}

int	redirect_in_out(int fd[2], t_proc *p, int index)
{
	if (!fd[0] && fd[1] != 1)
	{
		if (p->pfd)
			fd[1] = p->pfd[index * 2];
	}
	else if (fd[0] && fd[1] == 1)
	{
		if (p->pfd && index != p->lim)
			fd[0] = p->pfd[index * 2 - 1];
	}
	else if (!fd[0] && fd[1] == 1)
	{
		if (p->pfd)
		{
			if (index == 0)
				fd[0] = p->pfd[0];
			else if (index == p->lim)
				fd[1] = p->pfd[index * 2 - 1];
			else
			{
				fd[0] = p->pfd[index * 2];
				fd[1] = p->pfd[index * 2 - 1];
			}
		}
	}
	if (dup2(fd[0], 0) || dup2(fd[1], 1))
		return (errmsg_errno(5), 1);
	return (0);
}
