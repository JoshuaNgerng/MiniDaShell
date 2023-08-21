/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:52:48 by jngerng           #+#    #+#             */
/*   Updated: 2023/05/19 18:52:48 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	process_dupfd(t_pipfd pip, int mode)
{
	int	dup[2];
	int	out;

	out = 0;
	if (mode == 0)
	{
		dup[0] = pip.fd[0];
		dup[1] = pip.pfd[1];
	}
	if (mode == 1)
	{
		dup[0] = pip.pfd[0];
		dup[1] = pip.fd[1];
	}
	if (dup2(dup[0], 0) == -1 || dup2(dup[1], 1) == -1)
		out = handle_error_return("dup2", errno);
	if (close(pip.pfd[0]) == -1 || close(pip.pfd[1]) == -1)
		out = handle_error_return("fork close pipe", errno);
	if (close(pip.fd[0]) == -1 || close(pip.fd[1]) == -1)
		out = handle_error_return("fork_close file", errno);
	return (out);
}

static void	clear_err(char *exe, char **cmd, char **path)
{
	char	*name;

	if (!exe && cmd)
	{
		name = ft_strdup(cmd[0]);
		free(exe);
		ft_free_strs(cmd);
		if (path)
			ft_free_strs(path);
		handle_error_exit(name, -69);
	}
	if (cmd)
		ft_free_strs(cmd);
	if (exe)
		free(exe);
	if (path)
		ft_free_strs(path);
	exit(1);
}

static int	do_cmd(char **av, t_pipfd pip, char **env, int mode)
{
	int		pid;
	char	**cmd;
	char	*exe;

	exe = NULL;
	cmd = get_cmd(av[mode + 2]);
	if (cmd)
		exe = find_exe(cmd[0], pip.path);
	if (!exe || !cmd)
		clear_err(exe, cmd, pip.path);
	pid = fork();
	if (pid < 0)
		handle_error_return("fork", errno);
	if (pid == 0)
	{
		if (process_dupfd(pip, mode))
			clear_err(exe, cmd, pip.path);
		execve(exe, cmd, env);
		handle_error_return(cmd[0], errno);
		clear_err(exe, cmd, pip.path);
	}
	return (free(exe), ft_free_strs(cmd), pid);
}

static int	wait_clean(t_pipfd pip, int pid[2])
{
	int	output;

	output = 0;
	if (close(pip.pfd[0]) == -1)
		handle_error_return("main close pipe1", errno);
	if (close(pip.pfd[1]) == -1)
		handle_error_return("main close pipe2", errno);
	if (close(pip.fd[0]) == -1 || close(pip.fd[1]) == -1)
		handle_error_return("main close file", errno);
	if (pid[0] != -1)
		waitpid(pid[0], NULL, 0);
	if (pid[1] != -1)
		waitpid(pid[1], &output, 0);
	return (WEXITSTATUS(output));
}

int	main(int ac, char **av, char **env)
{
	t_pipfd	pip;
	int		i;
	int		pid[2];

	if (ac != 5)
		return (error_para(av[0]));
	i = -1;
	while (++ i < ac)
	{
		if (!av[i][0])
		{
			ft_printf(2, "bash: syntax error near unexpected token `|'\n");
			ft_printf(2, "empty command line\n");
			return (1);
		}
	}
	if (pipe(pip.pfd) == -1)
		return (handle_error_return("cannot make pipe", errno));
	pip.fd[0] = find_open(av, 0);
	pip.fd[1] = find_open(av, 1);
	pip.path = get_path(env);
	pid[1] = do_cmd(av, pip, env, 1);
	pid[0] = do_cmd(av, pip, env, 0);
	ft_free_strs(pip.path);
	return (wait_clean(pip, pid));
}
