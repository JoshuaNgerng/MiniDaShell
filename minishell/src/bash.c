/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:41:01 by jngerng           #+#    #+#             */
/*   Updated: 2023/08/18 19:41:01 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
assume everything is a pipe first
maybe need to change data structure for different oper ex || &&
handle cd and pwd differently
*/

int	make_pipes(t_proc *p)
{
	int	i;
	int	out;

	i = -1;
	out = 0;
	while (++ i < p->lim || !out)
	{
		if (pipe(&p->pfd[i * 2]) == -1)
		{
			errmsg_errno(2);
			out = 1;
		}
	}
	if (out)
	{
		i *= 2;
		while (i -- > 0)
			if (close(p->pfd[i]) == -1)
				sp_errmsg(0, "pipe: ");
	}
	return (out);
}

int	fork_child_processes(t_shell *s, t_proc *p, int *status)
{
	int		i;
	int		j;
	int		out;
	t_data	*d;

	i = -1;
	out = 0;
	d = p->data;
	while (++ i < p->num || !out)
	{
		p->pid[i] = fork_process(d, s, p->pfd, i);
		if (p->pid[i] < 0)
		{
			out = 1;
			errmsg_errno(1);
		}
		d = d->next;
	}
	if (!out)
		waitpid(p->pid[i], status, 0);
	while (i -- > 0)
		if (p->pid[i])
			kill(p->pid[i], SIGKILL);
	return (out);
}

int	bash_processes(t_shell *s, t_proc *p, int *status)
{
	int	len;
	int	out;
	int	i;
	
	s->sig = 0;
	out = 0;
	if (make_pipes(p))
		return (1);
	if (p->num > 1)
		out = fork_child_processes(s, p, status);
	else
	{
		len = ft_strlen(p->data->cmd[0]);
		if (ft_strncmp(p->data->cmd[0], "cd", len))
			out = ;
		else if (ft_strncmp(p->data->cmd[0], "export", len))
			out = ;
		else
			out = fork_child_processes(s, p, status);
	}
	if (clean_all_pipes(p->pfd, p->lim))
		out = 1;
	return (out);
}

int	do_bash(t_shell *s)
{
	int		i;
	int		status;
	t_proc	*buffer;

	if (!s->process)
		return (0);
	buffer = s->process;
	status = 0;
	while (buffer)
	{
		if (bash_processes(s, buffer, &status))
			return (1);
		if (!status && buffer->type == 'o')
			while (buffer && buffer->type == 'o')
				buffer = buffer->next;
		if (status && buffer->type == 'n')
			break ;
		buffer = buffer->next;
	}
	return (0);
}
