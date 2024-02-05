/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 03:56:03 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/05 13:19:00 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	free_reset(s);
	free(s->root.root_msg);
	free(s->root.prompt);
}

void	free_all_exit(t_shell *s, int ext_code)
{
	free_all(s);
	exit(ext_code);
}
