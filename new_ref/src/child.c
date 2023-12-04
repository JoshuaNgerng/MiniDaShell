/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 02:00:24 by jngerng           #+#    #+#             */
/*   Updated: 2023/12/04 22:04:53 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_helper(t_processor *p, int *fd_in, int *fd_out, int check)
{
	int	index_in;
	int	index_out;

	if (check == here_doc)
	{
		if (*fd_in > 0)
			close(*fd_in);
		*fd_in = p->here_doc_pipe[p->index_h * 2];
		printf("test here_doc pipe %d\n", *fd_in);
	}
	if (p->pipe)
	{
		if (*fd_in == 0 && p->index_p > 0)
		{
			index_in = (p->pipe_num - p->index_p) * 2;
			*fd_in = p->pipe[index_in];
		}
		if (*fd_out == 1 && p->index_p < p->pipe_num)
		{
			index_out = (p->pipe_num - p->index_p) * 2 - 1;
			*fd_out = p->pipe[index_out];
		}
	}
}

int	dup_stdin_stdout(t_shell *s, t_processor *p, t_proc *proc)
{
	int	fd_in;
	int	fd_out;

	fd_in = cycle_input_files(proc->f_read);
	fd_out = cycle_output_files(proc->f_out);
	if (fd_in < 0 || fd_out < 0)
		return (1);
	dup_helper(p, &fd_in, &fd_out, proc->in);
	if (dup2(fd_in, 0) == -1 || dup2(fd_out, 1) == -1)
		return (handle_error(s, 1), errmsg_errno(9), 1);
	close_pipes(p->pipe, p->pipe_num);
	close_pipes(p->here_doc_pipe, p->here_doc_num);
	return (0);
}

void	free_child_exit(t_shell *s, char **cmd, char *path_cmd, t_proc *hold)
{
	free_all(s);
	free_strs(cmd);
	if (path_cmd)
		free(path_cmd);
	free_process(hold);
	exit(s->status);
}

void	child_process(t_shell *s, t_processor *p, t_proc *hold)
{
	char	**cmd;
	char	*path_cmd;

	free_sect_list(p->buffer);
	p->buffer = NULL;
	cmd = NULL;
	path_cmd = NULL;
	if (dup_stdin_stdout(s, p, hold))
		free_child_exit(s, cmd, path_cmd, hold);
	if (!hold->cmd)
		free_child_exit(s, cmd, path_cmd, hold);
	cmd = get_cmd_array(hold->cmd);
	if (!cmd)
	{
		s->status = 137;
		free_child_exit(s, NULL, NULL, hold);
	}
	path_cmd = NULL;
	if (find_cmd(s->path, &path_cmd, cmd[0], &s->status))
		free_child_exit(s, cmd, path_cmd, hold);
	execve(path_cmd, cmd, s->env_ptr);
	free_child_exit(s, cmd, path_cmd, hold);
}

int	process_child(t_shell *s, t_processor *p, t_proc *hold)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (1);
	if (!pid)
		child_process(s, p, hold);
	else
	{
		p->pid[p->index_p] = pid;
		if (hold->here_doc)
			p->index_h ++;
	}
	return (0);
}
