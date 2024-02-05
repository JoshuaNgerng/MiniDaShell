/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:39:26 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/05 13:24:57 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_children_loop_sect(t_shell *s, t_processor *p, t_sect *sect)
{
	t_proc	*store;

	while (sect->block)
	{
		store = sect->block;
		sect->block = sect->block->next;
		if (prepare_env_n_path(s->env, p))
			return (clear_pipes(p), handle_error(s, 137), 1);
		if (process_child(s, p, store))
			return (clear_pipes(p), 1);
		free_process(store);
		if (p->env)
			free_strs(p->env);
		if (p->path)
			free_strs(p->path);
		p->env = NULL;
		p->path = NULL;
		p->index_p ++;
	}
	return (0);
}

static void	close_pipes_children(t_processor *p)
{
	close_pipes(p->pipe, p->pipe_num);
	if (p->stdin_ > 0)
		close(p->stdin_);
	if (p->stdout_ > 1)
		close(p->stdout_);
}

/*
builtins affect the main programme etc cd and export
therefore if builtins are called and the number of process is one
then the builtins will be runned in the main programme,
else it will sent to child process as usual
*/
static int	process_children(t_shell *s, t_processor *p, t_sect *sect)
{
	int	i;

	p->index_p = 0;
	if (prepare_pipes(p->pipe, p->pipe_num))
		return (1);
	signal(SIGINT, handle_ctrl_c_child);
	signal(SIGQUIT, handle_ctrl_z_child);
	if (process_children_loop_sect(s, p, sect))
		return (1);
	close_pipes_children(p);
	waitpid(p->pid[sect->pid - 1], &s->status, 0);
	signal(SIGINT, handle_sig_limbo);
	signal(SIGQUIT, handle_sig_limbo);
	i = sect->pid - 1;
	while (i -- > 0)
		waitpid(p->pid[i], NULL, 0);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	s->status = WEXITSTATUS(s->status);
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
	if (tokenize_and_sectioning(s, p))
		return (1);
	free(s->input);
	s->input = NULL;
	if (do_here_doc(s, p))
		return (1);
	while (p->buffer)
	{
		type = p->buffer->operator;
		if (bash_helper(s, p))
			return (1);
		ptr = p->buffer;
		p->buffer = p->buffer->next;
		free_sect(ptr);
		p->buffer = get_next_process(s, p->buffer, type);
	}
	clear_here_doc(p);
	return (0);
}
