/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pro_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:02:02 by jngerng           #+#    #+#             */
/*   Updated: 2023/05/25 14:02:02 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	process_dup(int in, int out, t_pip pip)
{
	int	i;
	int	t;

	t = 0;
	if (dup2(in, 0) == -1 || dup2(out, 1) == -1)
		t = handle_error_return("dup2", errno);
	i = -1;
	while (++ i < pip.max)
	{
		if (close(pip.pfd[i * 2]) == -1 || close(pip.pfd[i * 2 + 1]) == -1)
			t = handle_error_return("fork_close pipe", errno);
	}
	if (pip.fd_in == 0)
	{
		if (close(pip.fd_out) == -1)
			t = handle_error_return("fork_close file", errno);
	}
	else
	{
		if (close(pip.fd_in) == -1 || close(pip.fd_out) == -1)
			t = handle_error_return("fork_close file", errno);
	}
	return (t);
}

static int	process_dupfd(t_pip pip, int index)
{
	int	dup[2];

	if (pip.op == 0)
	{
		if (pip.mode == 0)
			dup[0] = pip.fd_in;
		else
			dup[0] = pip.pfd[(pip.max) * 2 - 2];
		dup[1] = pip.pfd[(pip.max) * 2 - 1 - (pip.mode * 2)];
	}
	if (pip.op == 2)
	{
		dup[0] = pip.pfd[0];
		dup[1] = pip.fd_out;
	}
	if (pip.op == 1)
	{
		dup[0] = pip.pfd[(pip.max - pip.mode - index) * 2];
		dup[1] = pip.pfd[(pip.max - pip.mode - index) * 2 - 1];
	}
	return (process_dup(dup[0], dup[1], pip));
}

static void	process_here_doc(char *limiter, t_pip pip, int *pid)
{
	int		l;
	int		e;
	int		x;
	char	*buffer;

	x = ft_strlen(limiter);
	buffer = get_next_line(0);
	e = 0;
	while (buffer)
	{
		l = ft_strlen(buffer);
		if (!strncmp(buffer, limiter, l - 1) && l - 1 == x)
			break ;
		e = write(pip.pfd[pip.max * 2 - 1], buffer, l);
		free(buffer);
		buffer = NULL;
		if (e != -1)
			buffer = get_next_line(0);
	}
	if (!buffer)
	{
		free_exit(pip, NULL, NULL, pid);
		handle_error_exit("here_doc", errno);
	}
	free(buffer);
}

static void	proc_exe(t_pip pip, char *exe, char **cmd, int *pid)
{
	if (process_dupfd(pip, pip.index))
		free_exit(pip, exe, cmd, pid);
	execve(exe, cmd, pip.p_env);
	handle_error_return(exe, errno);
	free_exit(pip, exe, cmd, pid);
	exit(0);
}

int	do_cmd(t_pip pip, char *in_cmd, int *s_pid)
{
	int		pid;
	char	**cmd;
	char	*exe;

	if (pip.mode == 1 && pip.op == 0)
		process_here_doc(pip.limit, pip, s_pid);
	exe = NULL;
	cmd = get_cmd(in_cmd);
	if (cmd)
		exe = find_exe(cmd[0], pip.paths);
	if (!exe || !cmd)
		free_exit(pip, exe, cmd, s_pid);
	pid = fork();
	if (pid < 0)
	{
		handle_error_return("fork", errno);
		free_exit(pip, exe, cmd, s_pid);
	}
	if (pid == 0)
		proc_exe(pip, exe, cmd, s_pid);
	return (ft_free_strs(cmd), free(exe), pid);
}
