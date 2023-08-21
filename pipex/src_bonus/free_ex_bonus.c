/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ex_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 18:30:57 by jngerng           #+#    #+#             */
/*   Updated: 2023/06/28 18:30:57 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	check_free(char *exe, char **cmd, int *pid)
{
	if (cmd)
		ft_free_strs(cmd);
	if (exe)
		free(exe);
	if (pid)
		free(pid);
}

void	free_exit(t_pip pip, char *exe, char **cmd, int *pid)
{
	char	*name;
	int		b;

	b = 0;
	if (!exe && cmd)
	{
		b = -69;
		name = ft_strdup(cmd[0]);
		if (!name)
			handle_error_return("free_exit strdup", errno);
	}
	check_free(exe, cmd, pid);
	ft_free_strs(pip.paths);
	free(pip.pfd);
	if (pip.fd_in > 0)
		if (close(pip.fd_in) == -1)
			handle_error_return("close", errno);
	if (close(pip.fd_out) == -1)
		handle_error_return("close", errno);
	if (b == -69)
		handle_error_exit(name, b);
	exit(1);
}
