/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:54:36 by jngerng           #+#    #+#             */
/*   Updated: 2023/05/24 17:54:36 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	check_sp(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[0] == '\'')
	{
		while (cmd[++ i])
			if (cmd[i] == '\'')
				break ;
	}
	if (cmd[0] == '\"')
	{
		while (cmd[++ i])
			if (cmd[i] == '\"' && cmd[i - 1] != '\\')
				break ;
	}
	if (cmd[i] == '\0')
	{
		ft_printf(2, "cannot process open quotation\n");
		return (-1);
	}
	return (i);
}

static int	proc_single(char *cmd, int lim)
{
	int	i;

	i = 0;
	cmd[i] = ' ';
	while (++ i < lim)
		if (cmd[i] == ' ')
			cmd[i] = -1;
	cmd[i] = ' ';
	return (i);
}

static int	proc_double(char *cmd, int lim)
{
	int	i;

	i = 0;
	cmd[i] = ' ';
	while (++ i < lim)
	{
		if (cmd[i] == ' ')
			cmd[i] = -1;
		if (cmd[i] == '\"' && cmd[i - 1] == '\\')
			cmd[i - 1] = -1;
	}
	cmd[i] = ' ';
	return (i);
}

static int	process_sp(char *cmd)
{
	int	i;
	int	out;

	i = check_sp(cmd);
	if (i == -1)
		return (-1);
	out = 0;
	if (cmd[0] == '\'')
		out = proc_single(cmd, i);
	if (cmd[0] == '\"')
		out = proc_double(cmd, i);
	return (out);
}

char	*handle_sp(char *cmd)
{
	int	i;
	int	j;

	i = process_sp(cmd);
	if (i == -1)
		return (NULL);
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			j = process_sp(&cmd[i]);
			if (j == -1)
				return (NULL);
			i += j;
		}
		i ++;
	}
	return (cmd);
}
