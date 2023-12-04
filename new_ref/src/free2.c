/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:50:32 by jngerng           #+#    #+#             */
/*   Updated: 2023/12/04 21:32:56 by jngerng          ###   ########.fr       */
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
	free(s->input);
	s->input = 0;
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
	s->processor.here_doc_pipe = 0;
	s->processor.here_doc_num = 0;
	s->processor.index_h = 0;
	s->processor.index_p = 0;
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
	// detach_node(&s->env, s->root.oldpwd);
	// free_env_node(s->root.oldpwd);
	// detach_node(&s->env, s->root.pwd);
	// free_env_node(s->root.pwd);
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
