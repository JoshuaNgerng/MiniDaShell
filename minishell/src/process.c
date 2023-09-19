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

int	handle_file_dup(t_data *d, t_shell *s, t_proc *p, int index)
{
	int	out;
	int	fd[2];

	out = 0;
	if (cycle_here_doc(d, p, index, &s->sig))
		out = 1;
	if (cycle_files(d, fd))
		out = 1;
	if (!out)
		if (redirect_in_out(fd, p, p->lim - index - s->sig))
			out = 1;
	if (clean_all_pipes(p->pfd, p->lim))
		out = 1;
	return (out);
}

int	fork_process(t_data *d, t_shell *s, t_proc *p, int index)
{
	int		pid;
	int		exe;
	char	*cmd;

	pid = fork();
	if (!pid)
	{
		exe = handle_file_dup(d, s, p, index);
		cmd = check_valid_cmd(d->cmd, s->path);
		if (!exe && cmd)
			execve(cmd, d->cmd, s->env);
		if (cmd)
			free(cmd);
		free_all(s);
		exit(1);
	}
	return (pid);
}

/*
make one func for cd and another for export
*/