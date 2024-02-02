/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:57:10 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/02 16:30:45 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_cmd_array(t_token *cmd)
{
	int		i;
	int		len;
	char	**out;
	t_token	*ptr;

	len = 1;
	ptr = cmd;
	while (ptr)
	{
		len ++;
		ptr = ptr->next;
	}
	out = (char **) malloc(len * sizeof(char *));
	if (!out)
		return (errmsg_errno(11), NULL);
	ptr = cmd;
	i = -1;
	while (++ i < len - 1)
	{
		out[i] = ptr->token;
		ptr->token = NULL;
		ptr = ptr->next;
	}
	out[i] = NULL;
	return (out);
}

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
	status = s->builtin[check - 1](s, cmd);
	if (fd_out > 1)
		close(fd_out);
	s->check = 0;
	return (free_strs(cmd), status);
}

static void	free_child_exit(t_shell *s, t_child *c, int exit_code)
{
	free_strs(c->cmd);
	if (c->path_cmd)
		free(c->path_cmd);
	free_process(c->hold);
	free_all(s);
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
	if (find_cmd(p->path, &c.path_cmd, c.cmd[0], &s->status))
		free_child_exit(s, &c, s->status);
	if (is_name(c.path_cmd))
		free_child_exit(s, &c, s->status);
	execve(c.path_cmd, c.cmd, p->env);
	free_child_exit(s, &c, 1);
}

// void	signal_child(t_shell *s)
// {
	// tcgetattr(0, &s->termios_);
	// s->termios_.c_lflag  |= !ECHOCTL;
	// tcsetattr(1, TCSANOW, &s->termios_);
// }

int	process_child(t_shell *s, t_processor *p, t_proc *hold)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (1);
	if (!pid)
	{
		if (hold->cmd)
			if (hold->cmd->type)
				subshell(s, p, hold);
		child_process(s, p, hold);
		exit(1);
	}
	else
	{
		p->pid[p->index_p] = pid;
		if (p->here_doc_pipe && hold->here_doc)
		{
			close(p->here_doc_pipe[p->index_h * 2]);
			close(p->here_doc_pipe[p->index_h * 2 + 1]);
			p->index_h ++;
		}
	}
	return (0);
}
