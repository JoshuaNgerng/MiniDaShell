/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:54:28 by jngerng           #+#    #+#             */
/*   Updated: 2023/05/24 17:54:28 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

static char	**get_paths(char **env)
{
	char	**paths;
	char	**buffer;
	char	*temp;

	paths = ft_split(help_path(env), ':');
	if (!paths)
		handle_error_exit("paths (split)", errno);
	buffer = paths;
	while (*buffer)
	{
		temp = *buffer;
		*buffer = ft_strjoin(*buffer, "/");
		if (!(*buffer))
		{
			ft_free_strs(paths);
			handle_error_exit("paths (strjoin)", errno);
		}
		free(temp);
		buffer ++;
	}
	return (paths);
}

static int	*get_pid_pip(t_pip *input)
{
	int	i;
	int	*pid;
	int	*pip;

	pip = (int *) malloc ((input -> max) * 2 * sizeof(int));
	if (!pip)
		handle_error_exit("get_pid_pip (malloc)", errno);
	pid = (int *) malloc ((input -> max - input -> mode + 1) * sizeof(int));
	if (!pid)
	{
		free(pip);
		handle_error_exit("get_pid_pip (malloc)", errno);
	}
	i = -1;
	while (++ i < input -> max)
	{
		if (pipe(&pip[i * 2]) == -1)
		{
			free(pip);
			free(pid);
			handle_error_exit("cannot make pipe", errno);
		}
	}
	input -> pfd = pip;
	return (pid);
}

static void	process_children(int **pid, t_pip pip, int ac, char **av)
{
	int	i;

	pid[0][pip.index] = do_cmd(pip, av[2 + pip.mode], *pid);
	i = 2 + pip.mode;
	pip.op = 1;
	while (++ i < ac - 2)
	{
		pip.index ++;
		pid[0][pip.index] = do_cmd(pip, av[i], *pid);
	}
	pip.index ++;
	pip.op = 2;
	pid[0][pip.index] = do_cmd(pip, av[ac - 2], *pid);
}

int	main(int ac, char **av, char **env)
{
	t_pip	pip;
	int		*pid;

	if (ac < 5)
		return (error_para(av[0]));
	if (check_empty(ac, av))
		return (1);
	pip = (struct s_pip){env, get_paths(env), NULL, NULL, 0, 0, 0, 0, 0, 0};
	pip.max = ac - 4;
	if (!ft_strncmp(av[1], "here_doc", 9))
	{
		pip.mode = 1;
		pip.limit = av[2];
	}
	if (ac - pip.mode < 5)
		return (ft_free_strs(pip.paths), error_para(av[0]));
	if (find_fd(&pip, av[1], av[ac -1]) == -1)
		return (ft_free_strs(pip.paths), 1);
	pid = get_pid_pip(&pip);
	process_children(&pid, pip, ac, av);
	return (wait_clean(pip, pid));
}
