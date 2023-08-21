/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 08:32:09 by jngerng           #+#    #+#             */
/*   Updated: 2023/05/22 08:32:09 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*help_path(char **env)
{
	char	**buffer;

	buffer = env;
	while (buffer)
	{
		if (!ft_strncmp(*buffer, "PATH", 4))
			break ;
		buffer ++;
	}
	return (*(buffer) + 5);
}

static char	*ft_strdup_error(const char *s)
{
	char	*out;

	out = ft_strdup(s);
	if (!out)
		handle_error_return("find (strdup)", errno);
	return (out);
}

char	**get_path(char **env)
{
	char	**out;
	char	**buffer;
	char	*temp;

	out = ft_split(help_path(env), ':');
	if (!out)
		handle_error_exit("path (split)", errno);
	buffer = out;
	while (*buffer)
	{
		temp = *buffer;
		*buffer = ft_strjoin(*buffer, "/");
		if (!(*buffer))
		{
			ft_free_strs(out);
			handle_error_exit("path (strjoin)", errno);
		}
		free(temp);
		buffer ++;
	}
	return (out);
}

char	*find_exe(char *cmd, char **path)
{
	char	*out;
	char	**buffer;

	out = NULL;
	buffer = path;
	while (*buffer)
	{
		out = ft_strjoin(*buffer, cmd);
		if (!out)
		{
			handle_error_return("find (strjoin)", errno);
			break ;
		}
		if (!access(out, F_OK | X_OK))
			break ;
		free(out);
		out = NULL;
		buffer ++;
	}
	if (!out)
		if (!access(cmd, F_OK | X_OK))
			return (ft_strdup_error(cmd));
	if (out)
		errno = 0;
	return (out);
}

char	**get_cmd(char *cmd)
{
	int		i;
	int		j;
	int		check;
	char	**output;

	check = ft_pip_strchr(cmd, "\"\'");
	if (check >= 0)
		if (!handle_sp(&cmd[check]))
			return (NULL);
	output = ft_split(cmd, ' ');
	if (!output)
		handle_error_return("cmd (split)", errno);
	if (output && check >= 0)
	{
		i = -1;
		while (output[++ i])
		{
			j = -1;
			while (output[i][++ j])
				if (output[i][j] < 0)
					output[i][j] = 32;
		}
	}
	return (output);
}
