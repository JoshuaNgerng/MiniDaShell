/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 09:14:19 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/01 11:36:27 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_errmsg_opt(char *name)
{
	errmsg_name(NULL);
	write(2, "does not support options for ", 29);
	write(2, name, ft_strlen(name));
	write(2, "\n", 1);
}

void	builtin_errmsg_arg(char *name)
{
	errmsg_name(NULL);
	write(2, "does not support arguments for ", 31);
	write(2, name, ft_strlen(name));
	write(2, "\n", 1);
}

int	check_options(char *cmd)
{
	if (cmd[0] == '-')
		return (1);
	return (0);
}

int	get_number_arg(char **cmd, int check)
{
	int	i;

	i = 0;
	while (cmd[++ i])
	{
		if (check)
		{
			if (check_options(cmd[i]))
				return (builtin_errmsg_opt(cmd[0]), -1);
		}
	}
	return (i);
}
