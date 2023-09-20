/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 02:49:31 by jngerng           #+#    #+#             */
/*   Updated: 2023/09/14 16:21:13 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
handle here_doc first 
cycle through all possible << 
then look at input
if cmd doesnt exit and input error then no output
else have output
*/

static int	empty_here_doc(char *lim)
{
	int		l;
	int		x;
	char	*buffer;	
	
	x = ft_strlen(lim);
	buffer = readline(">> ");
	while (buffer)
	{
		l = ft_strlen(buffer);
		if (!strncmp(buffer, lim, l - 1) && l - 1 == x)
			break ;
		free(buffer);
		buffer = NULL;
		buffer = readline(">> ");
	}
	if (!buffer)
		return (errmsg_errno(3), 1);
	return (free(buffer), 0);
}

static int	here_doc_write(char *lim, int pfd)
{
	int		l;
	int		x;
	int		e;
	char	*buffer;	
	
	x = ft_strlen(lim);
	buffer = readline(">> ");
	while (buffer)
	{
		l = ft_strlen(buffer);
		if (!strncmp(buffer, lim, l - 1) && l - 1 == x)
			break ;
		e = write(pfd, buffer, l);
		free(buffer);
		buffer = NULL;
		if (e != -1)
			buffer = readline(">> ");
	}
	if (!buffer && e == -1)
		return (errmsg_errno(4), 1);
	if (!buffer)
		return (errmsg_errno(3), 1);
	return (free(buffer), 0);
}

int	cycle_output_files(t_data *d)
{
	int	i;
	int	fd;

	if (!d->f_out->f_name)
		return (0);
	i = -1;
	fd = 0;
	while (d->f_out[++ i].f_name)
	{
		if (fd)
			close(fd);
		if (d->f_out[i].f_type == 'w')
			fd = open(d->f_out[i].f_name, O_WRONLY | O_CREAT | O_TRUNC, 0660);
		else if (d->f_out[i].f_type == 'a')
			fd = open(d->f_out[i].f_name, O_WRONLY | O_CREAT | O_APPEND, 0660);
		if (fd == -1)
			return (sp_errmsg(3, d->f_out[i].f_name), -1);
	}
	return (fd);
}

int	cycle_input_files(t_data *d)
{
	int	i;
	int	fd;

	if (!d->f_read[0])
		return (0);
	i = 0;
	fd = open(d->f_read[0], O_RDONLY);
	while (d->f_read[++ i])
	{
		if (fd == -1)
			return (sp_errmsg(3, d->f_read[i - 1]), -1);
		close(fd);
		fd = open(d->f_read[i], O_RDONLY);
	}
	if (fd < -1)
		return (sp_errmsg(3, d->f_read[i]), -1);
	return (fd);
}

int	cycle_files(t_data *d, int fd[2])
{
	fd[0] = 0;
	fd[1] = 1;
	if (d->in == 'r')
		fd[0] = cycle_input_files(d);
	if (fd[0] < 0)
		return (1);
	if (d->out)
		fd[1] = cycle_output_files(d);
	if (fd[1] < 0)
	{
		if (fd[0] > 0)
			close(fd[0]);
		return (1);
	}
	return (0);
}

int	cycle_here_doc(t_data *d, t_proc *p, int index, int *add)
{
	int	i;
	int	pfd;

	if (!d->here_doc || !d->here_doc[0])
		return (0);
	while (d->here_doc[++ i])
	{
		if (!d->here_doc[i + 1])
			break ;
		if (empty_here_doc(d->here_doc[i]))
			return (1);
	}
	if (d->in != 'h')
		return (empty_here_doc(d->here_doc[i]));
	(*add)++;
	pfd = p->pfd[(p->lim - index - *(add)) * 2 - 1];
	return (here_doc_write(d->here_doc[i], pfd));
}