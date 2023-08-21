/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:54:51 by jngerng           #+#    #+#             */
/*   Updated: 2023/05/24 17:54:51 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*ft_strdup_error(const char *s)
{
	char	*out;

	out = ft_strdup(s);
	if (!out)
		handle_error_return("find (strdup)", errno);
	return (out);
}

char	*find_exe(char *cmd, char **paths)
{
	char	*out;
	char	**buffer;

	out = NULL;
	if (!cmd)
		return (NULL);
	buffer = paths;
	while (*buffer)
	{
		out = ft_strjoin(*buffer, cmd);
		if (!out)
		{
			handle_error_return("find (strjoin)", errno);
			return (NULL);
		}
		if (!access(out, F_OK | X_OK))
			return (out);
		free(out);
		out = NULL;
		buffer ++;
	}
	if (!access(cmd, F_OK | X_OK) && !out)
		out = ft_strdup_error(cmd);
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

int	find_fd(t_pip *pip, char *file_in, char *file_out)
{
	if (pip->mode == 0)
		pip->fd_in = open(file_in, O_RDONLY);
	if (pip->fd_in < 0)
		return (handle_error_return(file_in, errno));
	if (pip->mode == 1)
		pip->fd_out = open(file_out, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		pip->fd_out = open(file_out, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pip->fd_out < 0)
	{
		close(pip->fd_in);
		return (handle_error_return(file_out, errno));
	}
	return (0);
}

int	wait_clean(t_pip pip, int *pid)
{
	int	i;
	int	x;
	int	output;

	i = -1;
	output = 0;
	ft_free_strs(pip.paths);
	while (++ i < pip.max)
	{
		x = i * 2;
		if (close(pip.pfd[x]) == -1 || close(pip.pfd[x + 1]) == -1)
			handle_error_return("main close pipe", errno);
	}
	i = -1;
	while (++ i < pip.max - pip.mode)
		waitpid(pid[i], NULL, 0);
	waitpid(pid[i], &output, 0);
	if (close(pip.fd_in) == -1 || close(pip.fd_out) == -1)
		handle_error_return("main close file", errno);
	return (free(pip.pfd), free(pid), WEXITSTATUS(output));
}
