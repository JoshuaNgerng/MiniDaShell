/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:54:41 by jngerng           #+#    #+#             */
/*   Updated: 2023/05/24 17:54:41 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_pip_strchr(const char *s, const char *c)
{
	int	i;

	i = 0;
	while (ft_checkset(s[i], c) == 0 && s[i] != '\0')
	{
		i ++;
		if (s[i] == '\"')
		{
			if (s[i - 1] == '\\')
				i ++;
		}
	}
	if (!s[i])
		return (-1);
	return (i);
}

int	error_para(char *name)
{
	ft_printf(2, "%s: insufficient parameter\n", &name[2]);
	return (1);
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
	return (-1);
}

int	check_empty(int ac, char **av)
{
	int	i;

	i = -1;
	while (++ i < ac)
	{
		if (!av[i][0])
		{
			ft_printf(2, "syntax error near unexpected token `|'\n");
			ft_printf(2, "empty command line\n");
			return (1);
		}
	}
	return (0);
}
