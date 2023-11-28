/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:50:32 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/28 12:54:00 by jngerng          ###   ########.fr       */
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

void	free_all_exit(t_shell *s, int ext_code)
{
	free_all(s);
	exit(ext_code);
}

void	free_env_node(t_env *env)
{
	if (!env)
		return ;
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	free(env);
}

void	free_env_list(t_env *list)
{
	t_env	*ptr;

	while (list)
	{
		ptr = list;
		list = list->next;
		free_env_node(ptr);
	}
}