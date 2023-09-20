/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 09:33:59 by jngerng           #+#    #+#             */
/*   Updated: 2023/09/14 15:42:36 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exit_err(t_shell *s, t_proc *p)
{
	free_all(s);
	clean_all_pipes(p->pfd, p->lim);
	exit(1);
}

int	handle_file_dup(t_data *d, t_shell *s, t_proc *p, int index)
{
	int	out;
	int	fd[2];

	out = 0;
	if (cycle_files(d, fd))
		out = 1;
	printf("files fd %d %d\n", fd[0], fd[1]);
	printf("test indexing lim:%d, index:%d, sig:%d fin:%d\n", p->lim, index, s->sig,  p->lim - index - s->sig);
	if (!out)
		if (redirect_in_out(fd, p, p->lim - index - s->sig))
			out = 1;
	if (clean_all_pipes(p->pfd, p->lim))
		out = 1;
	printf("test fd %d %d\n", fd[0], fd[1]);
	if (fd[0] > 0)
		close(fd[0]);
	if (fd[1] > 1)
		close(fd[1]);
	return (out);
}

int	fork_process(t_data *d, t_shell *s, t_proc *p, int index)
{
	int		pid;
	int		exe;
	char	*cmd;

	exe = cycle_here_doc(d, p, index, &s->sig);
	pid = fork();
	if (!pid)
	{
		if (exe)
			free_exit_err(s, p);
		if (handle_file_dup(d, s, p, index))
			free_exit_err(s, p);
		cmd = check_valid_cmd(d->cmd, s->path);
		if (cmd)
		{
			execve(cmd, d->cmd, s->env);
			free(cmd);
		}
		free_exit_err(s, p);
	}
	return (pid);
}

/*
make one func for cd and another for export
*/