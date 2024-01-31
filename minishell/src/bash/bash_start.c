/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:39:26 by jngerng           #+#    #+#             */
/*   Updated: 2024/01/31 14:50:36 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_builtins(t_shell *s, t_proc *p, int check)
{
	int		fd_in;
	int		fd_out;
	int		status;
	char	**cmd;

	fd_in = cycle_input_files(p->f_read);
	fd_out = cycle_output_files(p->f_out);
	if (fd_in > 0)
		close(fd_in);
	if (fd_out > 1)
		s->check = fd_out;
	cmd = get_cmd_array(p->cmd);
	if (!cmd)
		return (handle_error(s, 137), 1);
	// printf("test builtins\n");
	status = s->builtin[check - 1](s, cmd);
	if (fd_out > 1)
		close(fd_out);
	s->check = 0;
	return (free_strs(cmd), status);
}

static t_sect	*get_next_process(t_shell *s, t_sect *buffer, int type)
{
	int		skip;
	t_sect	*ptr;

	skip = 0;
	if (type == _or && !s->status)
		skip = type;
	else if (type == _and && s->status)
		skip = type;
	if (skip)
	{
		while (buffer && buffer->operator != skip)
		{
			ptr = buffer;
			buffer = buffer->next;
			free_sect(ptr);
		}
		if (buffer)
		{
			ptr = buffer;
			buffer = buffer->next;
			free_sect(ptr);
		}
	}
	return (buffer);
}

/*
builtins affect the main programme etc cd and export
therefore if builtins are called and the number of process is one
then the builtins will be runned in the main programme,
else it will sent to child process as usual
*/
static int	process_children(t_shell *s, t_processor *p, t_sect *sect)
{
	int		i;
	t_proc	*store;

	p->index_p = 0;
	if (prepare_pipes(p->pipe, p->pipe_num))
		return (1);
	while (sect->block)
	{
		store = sect->block;
		sect->block = sect->block->next;
		store->next = NULL;
		if (process_child(s, p, store))
			return (clear_pipes(p), 1);
		free_process(store);
		p->index_p ++;
	}
	// printf("test1\n");
	close_pipes(p->pipe, p->pipe_num);
	if (p->stdin_ > 0)
		close(p->stdin_);
	if (p->stdout_ > 1)
		close(p->stdout_);
	// printf("test2 %p\n", p->pid);
	i = -1;
	while (++ i < sect->pid)
		waitpid(p->pid[i], &s->status, 0);
	s->status = WEXITSTATUS(s->status);
	// printf("test3\n");
	free(p->pipe);
	p->pipe = NULL;
	p->stdin_ = 0;
	p->stdout_ = 1;
	return (0);
}

static int	bash_helper(t_shell *s, t_processor *p)
{
	int	check;

	p->pipe_num = p->buffer->pid - 1;
	p->pid = (int *) malloc(p->buffer->pid * sizeof(int));
	p->pipe = (int *) malloc(p->pipe_num * sizeof(int) * 2);
	if (!p->pid || !p->pipe)
		return (errmsg_errno(23), handle_error(s, 137), 1);
	if (expand(s, p->buffer))
		return (1);
	if (p->pipe_num == 0)
	{
		check = check_builtins(p->buffer->block);
		if (check)
			return (process_builtins(s, p->buffer->block, check));
	}
	if (process_children(s, p, p->buffer))
		return (1);
	free(p->pid);
	p->pid = NULL;
	return (0);
}

/*
split input line into sections
each sections would be further process into
structs to rep different parts of a process
heredoc (if present) always runs first
and store into pipes (regardless of order in section or process)
bash helper create space for pipes and process ids,
then expand and $ symbol and remove '/"
children processes are made and excuted
depending on the exit status of the last process,
the sections are loop till a valid process is found
*/
int	bash(t_shell *s)
{
	int			type;
	t_processor	*p;
	t_sect		*ptr;

	p = &s->processor;
	// printf("processing\n");
	if (tokenize_and_sectioning(s, p))
		return (1);
	// dev_print_sect(p->buffer);
	free(s->input);
	s->input = NULL;
	if (do_here_doc(s, p))
		return (1);
	// printf("test %p\n", p->buffer);
	while (p->buffer)
	{
		type = p->buffer->operator;
		// printf("test\n");
		if (bash_helper(s, p))
			return (1);
		ptr = p->buffer;
		p->buffer = p->buffer->next;
		free_sect(ptr);
		p->buffer = get_next_process(s, p->buffer, type);
	}
	// printf("test\n");
	clear_here_doc(p);
	return (0);
}
