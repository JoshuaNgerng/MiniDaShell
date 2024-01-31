/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:41:41 by jngerng           #+#    #+#             */
/*   Updated: 2024/01/30 11:15:11 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_sect(t_sect *sec)
{
	free_process(sec->block);
	free(sec);
}

void	free_sect_list(t_sect *list)
{
	t_sect	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free_sect(tmp);
	}
}

void	free_reset(t_shell *s)
{
	s->check = 0;
	if (s->input)
	{
		free(s->input);
		s->input = NULL;
	}
	free_sect_list(s->processor.buffer);
	s->processor.buffer = NULL;
	if (s->processor.pid)
		free(s->processor.pid);
	if (s->processor.pipe)
		free(s->processor.pipe);
	if (s->processor.here_doc_pipe)
		free(s->processor.here_doc_pipe);
	s->processor.pid = NULL;
	s->processor.pipe = NULL;
	s->processor.here_doc_pipe = NULL;
	s->processor.here_doc_num = 0;
	s->processor.pipe_num = 0;
	s->processor.index_h = 0;
	s->processor.index_p = 0;
	s->processor.stdin_ = 0;
	s->processor.stdout_ = 1;
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

void	free_all(t_shell *s)
{
	free_strs(s->path);
	free_env_list(s->env);
	free_reset(s);
	free(s->root.root_msg);
	free(s->root.prompt);
}

void	free_all_exit(t_shell *s, int ext_code)
{
	free_all(s);
	exit(ext_code);
}
