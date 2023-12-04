/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:06:43 by jngerng           #+#    #+#             */
/*   Updated: 2023/12/04 21:36:33 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (!ft_strncmp(buffer, lim, l) && l == x)
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
		if (!strncmp(buffer, lim, l) && l == x)
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

int	loop_here_doc_helper(t_shell *s, t_token *t, int *pfd, int *index)
{
	int		i;
	t_token	*ptr;

	ptr = t;
	while (ptr)
	{
		if (!ptr->next)
			break ;
		if (expand_here_doc(s, ptr))
			return (1);
		if (empty_here_doc(ptr->token))
			return (1);
		ptr = ptr->next;
	}
	if (ptr)
	{
		i = *index;
		printf("test here doc fd %d\n", pfd[i * 2 + 1]);
		if (here_doc_write(ptr->token, pfd[i * 2 + 1]))
			return (1);
		*index = i + 1;
	}
	return (0);
}

int	loop_here_doc(t_shell *s, t_processor *p, int *pfd)
{
	int		i;
	t_sect	*ptr;
	t_proc	*ptr2;

	i = 0;
	ptr = p->buffer;
	while (ptr)
	{
		ptr2 = ptr->block;
		while (ptr2)
		{
			if (loop_here_doc_helper(s, ptr2->here_doc, pfd, &i))
				return (1);
			ptr2 = ptr2->next;
		}
		ptr = ptr->next;
	}
	return (0);
}
