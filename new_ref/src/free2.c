/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:50:32 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/22 08:24:51 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_process_section(t_shell *s)
{
	free_processes(s->process_section.proc);
	free(s->process_section.pfd);
	free(s->process_section.pid);
	s->process_section = (t_block){0, 0, 0, 0, 0, 0, 0};
}

void	free_reset(t_shell *s)
{
	s->check = 0;
	free(s->input);
	s->input = 0;
	free_process_section(s);
}

void	free_all(t_shell *s)
{
	free_strs(s->path);
	// free_blocks(s->input);
	free(s->root.root_msg);
	free(s->root.prompt);
	free_process_section(s);
}
