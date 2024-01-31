/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 03:07:13 by jngerng           #+#    #+#             */
/*   Updated: 2024/01/31 08:56:41 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes_subshell(int *pipes, int len, int fd_in, int fd_out)
{
	int	i;

	i = -1;
	while (++ i < len)
	{
		if (pipes[i] != fd_in && pipes[i] != fd_out)
			close(pipes[i]);
	}
}

void	free_close_pipes_subshell(t_processor *p, t_fd *fd)
{
	if (p->pipe)
	{
		close_pipes_subshell(p->pipe, p->pipe_num, fd->fd_in, fd->fd_out);
		free(p->pipe);
		p->pipe = NULL;
	}
	if (p->here_doc_pipe)
	{
		close_pipes_subshell(p->here_doc_pipe, p->here_doc_num,
			fd->fd_in, fd->fd_out);
		free(p->here_doc_pipe);
		p->here_doc_pipe = NULL;
	}
	if (fd->read_ != fd->fd_in && fd->read_ > 0)
		close(fd->read_);
	if (fd->write_ != fd->fd_out && fd->write_ > 1)
		close(fd->write_);
}

void	subshell(t_shell *s, t_processor *p, t_proc *hold)
{
	int		len;
	t_fd	fd;

	// printf("test\n");
	free_sect_list(p->buffer);
	len = ft_strlen(hold->cmd->token);
	// printf("test:%s\n", hold->cmd->token);
	hold->cmd->token[len - 1] = '\0';
	ft_memmove(hold->cmd->token, &hold->cmd->token[1], len);
	// printf("test:%s\n", hold->cmd->token);
	p->buffer = NULL;
	fd.read_ = cycle_input_files(hold->f_read);
	fd.write_ = cycle_output_files(hold->f_out);
	fd.fd_in = fd.read_;
	fd.fd_out = fd.write_;
	if (fd.read_ < 0 || fd.write_ < 0)
		free_all_exit(s, 1);
	dup_helper(p, &fd, hold->in);
	// printf("test fd_out(%d) fd_in(%d)\n", fd.fd_out, fd.fd_in);
	// free_reset(s);
	if (fd.fd_in > 0)
		p->stdin_ = fd.fd_in;
	if (fd.fd_out > 1)
		p->stdout_ = fd.fd_out;
	// printf("test stdout(%d) stdin(%d)\n", p->stdout_, p->stdin_);
	free_close_pipes_subshell(p, &fd);
	s->input = hold->cmd->token;
	hold->cmd->token = NULL;
	free_process(hold);
	bash(s);
	free_all_exit(s, s->status);
}
