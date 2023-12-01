/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 03:16:07 by jngerng           #+#    #+#             */
/*   Updated: 2023/12/01 14:16:50 by jngerng          ###   ########.fr       */
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
		f_out = f_out->next;
		if (!f_out->next)
			break ;
		close(fd);
	}
	if (fd < -1)
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
		f_read = f_read->next;
		if (!f_read->next)
			break ;
		close(fd);
	}
	if (fd < -1)
		return (sp_errmsg(3, f_read->token), -1);
	return (fd);
}
