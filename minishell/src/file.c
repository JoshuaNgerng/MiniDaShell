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
	int		i;
	int		x;
	char	*buffer;	
	
	e = 0;
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
	int		i;
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

int	cycle_both_output(char *w1, char *a1, char *w, char *a, int fd[2])
{
	if (fd[0] == -1 || fd[1] == -1)
	{
		if (fd[0] > 0)
		{
			if (fd[1] > 0)
				close(fd[1]);
			return (sp_errmsg(), -1);
		}
		close(fd[0]);
		return (sp_errmsg(), -1);
	}
	close(fd[0]);
	close(fd[1]);
	fd[0] = open(w, O_WRONLY | O_CREAT | O_TRUNC, 0660);
	fd[1] = open(a, O_WRONLY | O_CREAT | O_APPEND, 0660);
}

int	cycle_leftover_output(char **file, int fd, char type, int (*f)(char *, int , mode_t))
{
	int		i;
	int		flags;
	mode_t	mode;

	if (type == 'w')
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else
		flags = O_WRONLY | O_CREAT | O_APPEND;
	mode = 0660;
	i = -1;
	while (file[++ i])
	{
		if (fd == -1)
			return (sp_errmsg(), -1);
		close(fd);
		fd = f(file[i], flags, mode);
	}
	return (fd);
}

int	cycle_output_files(t_data *d)
{
	int	i;
	int	fd[2];

	if (!d->f_write[0] && !d->f_append[0])
		return (0);
	i = 0;
	if (d->f_write[0])
		fd[0] = open(d->f_write[0], O_WRONLY | O_CREAT | O_TRUNC, 0660);
	if (d->f_append[0])
		fd[1] = open(d->f_append[0], O_WRONLY | O_CREAT | O_APPEND, 0660);
	while (d->f_write[++ i] && d->f_append[i])
	{
		;
		if (cycle_both_output(d->f_write[i], d->f_append[i], fd))
			return (1);
	}
	if (d->f_write[i])
		fd[0] = cycle_leftover_output(&d->f_write[i], fd[0], 'w', &open);
	if (d->f_append[i])
		fd[1] = cycle_leftover_output(&d->f_append[i], fd[1], 'a', &open);
	if (d->out == 'a')
	{
		if (fd[0] > 0)
			close(fd[0]);
		return (fd[1]);
	}
	if (fd[1] > 0)
		close(fd[1]);
	return (fd[0]);
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
			return (sp_errmsg(3, f_read[i - 1]), -1);
		close(fd);
		fd = open(d->f_read[i], O_RDONLY);
	}
	if (fd < -1)
		return (sp_errmsg(3, f_read[i]), -1);
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
		return (1);
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
	pfd = p->pfd[(p->lim - index - s->sig) * 2 - 1];
	return (here_doc_write(d->here_doc[i], pfd));
}