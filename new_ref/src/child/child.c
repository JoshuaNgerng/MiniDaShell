/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:57:10 by jngerng           #+#    #+#             */
/*   Updated: 2024/01/30 13:23:17 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_child_exit(t_shell *s, t_child *c, int exit_code)
{
	free_all(s);
	free_strs(c->cmd);
	if (c->path_cmd)
		free(c->path_cmd);
	free_process(c->hold);
	exit(exit_code);
}

static void	child_process(t_shell *s, t_processor *p, t_proc *hold)
{
	int		check;
	t_child	c;

	c = (t_child){NULL, NULL, hold};
	free_sect_list(p->buffer);
	p->buffer = NULL;
	if (dup_stdin_stdout(s, p, hold))
		free_child_exit(s, &c, s->status);
	if (!hold->cmd)
		free_child_exit(s, &c, s->status);
	check = check_builtins(hold);
	c.cmd = get_cmd_array(hold->cmd);
	if (!c.cmd)
		free_child_exit(s, &c, 137);
	if (check)
		free_child_exit(s, &c, s->builtin[check - 1](s, c.cmd));
	if (find_cmd(s->path, &c.path_cmd, c.cmd[0], &s->status))
		free_child_exit(s, &c, s->status);
	execve(c.path_cmd, c.cmd, s->env_ptr);
	free_child_exit(s, &c, 1);
}

int	process_child(t_shell *s, t_processor *p, t_proc *hold)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (1);
	if (!pid)
	{
		// printf("test type %d\n", hold->cmd->type);
		// child_process(s, p, hold);
		if (!hold->cmd->type)
			child_process(s, p, hold);
		else
			subshell(s, p, hold);
	}
	else
	{
		p->pid[p->index_p] = pid;
		if (p->here_doc_pipe)
		{
			close(p->here_doc_pipe[p->index_h * 2]);
			close(p->here_doc_pipe[p->index_h * 2 + 1]);
		}
		if (hold->here_doc)
			p->index_h ++;
	}
	return (0);
}
