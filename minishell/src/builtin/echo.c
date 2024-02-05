/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:12:06 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/05 16:06:24 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_end(int fd, int check, int *status)
{
	if (!check)
		write(fd, "\n", 1);
	*status = 0;
}

static void	check_echo_args(char **arg, int *i, int *check)
{
	int	index;

	index = *i;
	while (arg[++index])
	{
		if (!arg[index])
			return ;
		if (!ft_strncmp(arg[index], "-n", 3))
		{
			*check = 1;
			*i = index;
		}
		else
			return ;
	}
}

int	echo_function(t_shell *s, char **cmd)
{
	int	check;
	int	fd;
	int	i;

	fd = 1;
	i = 0;
	check = 0;
	if (s->check)
		fd = s->check;
	check_echo_args(cmd, &i, &check);
	if (!cmd[i] || !cmd[i + 1])
		return (echo_end(fd, check, &s->status), 0);
	while (cmd[++ i])
	{
		if (!cmd[i + 1])
			break ;
		write(fd, cmd[i], ft_strlen(cmd[i]));
		write(fd, " ", 1);
	}
	if (cmd[i])
		write(fd, cmd[i], ft_strlen(cmd[i]));
	return (echo_end(fd, check, &s->status), 0);
}
