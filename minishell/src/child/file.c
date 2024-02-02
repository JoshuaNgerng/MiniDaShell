/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:56:00 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/02 09:51:10 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cycle_output_files(t_token *f_out)
{
	int	fd;

	fd = 1;
	if (!f_out)
		return (fd);
	while (f_out)
	{
		if (f_out->type == _write)
			fd = open(f_out->token, O_WRONLY | O_CREAT | O_TRUNC, 0660);
		else
			fd = open(f_out->token, O_WRONLY | O_CREAT | O_APPEND, 0660);
		if (fd == -1)
			return (sp_errmsg(3, f_out->token), -1);
		if (!f_out->next)
			break ;
		f_out = f_out->next;
		close(fd);
	}
	if (fd < 0)
		return (sp_errmsg(3, f_out->token), -1);
	return (fd);
}

int	cycle_input_files(t_token *f_read)
{
	int	fd;

	fd = 0;
	if (!f_read)
		return (0);
	while (f_read)
	{
		fd = open(f_read->token, O_RDONLY);
		if (fd == -1)
			return (sp_errmsg(3, f_read->token), -1);
		if (!f_read->next)
			break ;
		f_read = f_read->next;
		close(fd);
	}
	if (fd < 0)
		return (sp_errmsg(3, f_read->token), -1);
	return (fd);
}

void	dup_helper(t_processor *p, t_fd *fd, int check)
{
	int	index_in;
	int	index_out;

	if (check == here_doc)
		fd->fd_in = p->here_doc_pipe[p->index_h * 2];
	if (p->pipe)
	{
		if (fd->fd_in == 0 && p->index_p > 0)
		{
			index_in = (p->pipe_num - p->index_p) * 2;
			fd->fd_in = p->pipe[index_in];
		}
		if (fd->fd_out == 1 && p->index_p < p->pipe_num)
		{
			index_out = (p->pipe_num - p->index_p) * 2 - 1;
			fd->fd_out = p->pipe[index_out];
		}
	}
}

static void	close_extra_fd(int read_, int write_, int in, int out)
{
	if (read_ > 0)
		close(read_);
	if (write_ > 1)
		close(write_);
	if (in > 0)
		close(in);
	if (out > 1)
		close(out);
}

int	dup_stdin_stdout(t_shell *s, t_processor *p, t_proc *proc)
{
	t_fd	fd;

	fd.read_ = cycle_input_files(proc->f_read);
	if (fd.read_ < 0)
		return (1);
	fd.write_ = cycle_output_files(proc->f_out);
	if (fd.write_ < 0)
		return (1);
	fd.fd_in = fd.read_;
	fd.fd_out = fd.write_;
	dup_helper(p, &fd, proc->in);
	if (!fd.fd_in)
		fd.fd_in = p->stdin_;
	if (fd.fd_out == 1)
		fd.fd_out = p->stdout_;
	if (dup2(fd.fd_in, 0) == -1 || dup2(fd.fd_out, 1) == -1)
		return (handle_error(s, 1), errmsg_errno(9), 1);
	close_pipes(p->pipe, p->pipe_num);
	clear_here_doc(p);
	return (close_extra_fd(fd.read_, fd.write_, p->stdin_, p->stdout_), 0);
}
