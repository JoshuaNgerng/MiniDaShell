/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:04:54 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/07 09:47:51 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_ext_code(int *ext_code, int value)
{
	*ext_code = value;
}

static char	*find_shell_cmd(char **path, char *cmd, int *ext_code)
{
	int		i;
	char	*out;

	i = -1;
	out = NULL;
	if (!path)
		return (NULL);
	while (path[++ i])
	{
		out = ft_strjoin(path[i], cmd);
		if (!out)
			return (set_ext_code(ext_code, 137), NULL);
		if (!test_whether_is_file(out))
			return (out);
		free(out);
		out = NULL;
	}
	return (set_ext_code(ext_code, 127), out);
}

static int	search_path(char **path, char **path_cmd, char *cmd, int *ext_code)
{
	char	*find_cmd;

	find_cmd = find_shell_cmd(path, cmd, ext_code);
	if (!find_cmd)
	{
		if (*ext_code == 137)
			return (errmsg_errno(10), 1);
		return (errmsg_var(3, cmd, ft_strlen(cmd)), 1);
	}
	*path_cmd = find_cmd;
	return (0);
}

static void	check_err(int check, int *ext_code, char *cmd)
{
	if (check == -1)
	{
		set_ext_code(ext_code, 127);
		errmsg_var(3, cmd, ft_strlen(cmd));
	}
	if (check == 1)
	{
		set_ext_code(ext_code, 126);
		errmsg_var(4, cmd, ft_strlen(cmd));
	}
}

int	find_cmd(char **path, char **path_cmd, char *cmd, int *ext_code)
{
	int		check;
	char	*ptr;

	if (!cmd)
		return (0);
	ptr = ft_strrchr(cmd, '/');
	if (!ptr)
		return (search_path(path, path_cmd, cmd, ext_code));
	check = test_whether_is_file(cmd);
	if (!check)
	{
		*path_cmd = ft_strdup(cmd);
		if (!(*path_cmd))
			return (set_ext_code(ext_code, 137), errmsg_errno(10), 1);
		return (0);
	}
	return (check_err(check, ext_code, cmd), 1);
}
