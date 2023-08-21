/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:18:05 by jngerng           #+#    #+#             */
/*   Updated: 2023/05/20 20:18:05 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_pip_strchr(const char *s, const char *c)
{
	int	i;

	i = 0;
	while (ft_checkset(s[i], c) == 0 && s[i])
	{
		i ++;
		if (s[i] == '\"')
		{
			if (s[i - 1] == '\\')
				i ++;
		}
	}
	if (ft_checkset(s[i], c) == 0)
		return (-1);
	return (i);
}

int	error_para(char *name)
{
	ft_printf(2, "%s: insufficient parameter\n", &name[2]);
	return (0);
}

void	handle_error_exit(char *errmsg, int error)
{
	if (error == -69)
	{
		ft_printf(2, "%s: command not found\n", errmsg);
		free(errmsg);
		exit(127);
	}
	ft_printf(2, "%s: %s\n", errmsg, strerror(error));
	exit(1);
}

int	handle_error_return(char *errmsg, int error)
{
	ft_printf(2, "%s: %s\n", errmsg, strerror(error));
	errno = 0;
	return (1);
}

int	find_open(char **av, int mode)
{
	int		fd;
	char	*name;

	fd = -2;
	name = NULL;
	if (mode == 0)
	{
		fd = open(av[1], O_RDONLY);
		name = av[1];
	}
	if (mode == 1)
	{
		fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		name = av[4];
	}
	if (fd < 0)
	{
		if (mode == 0)
			close(fd);
		handle_error_exit(name, errno);
	}
	return (fd);
}
