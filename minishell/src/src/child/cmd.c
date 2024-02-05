/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:04:54 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/02 13:06:37 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_ext_code(int *ext_code, int value)
{
	*ext_code = value;
}

static int	test_whether_is_file(const char *name)
{
	struct stat	statbuf;

	if (access(name, F_OK | X_OK))
		return (-1);
	if (stat(name, &statbuf))
		return (-2);
	if (S_ISREG(statbuf.st_mode) == 1 && !S_ISDIR(statbuf.st_mode))
		return (0);
	if (S_ISDIR(statbuf.st_mode) == 1)
		return (1);
	return (-3);
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

int	find_cmd(char **path, char **path_cmd, char *cmd, int *ext_code)
{
	int		check;
	char	*ptr;

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
	return (1);
}
