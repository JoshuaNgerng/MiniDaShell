/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preproc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 04:31:26 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/01 05:45:19 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_total_env(t_env *env)
{
	int		n;
	t_env	*ptr;

	n = 0;
	ptr = env;
	while (ptr)
	{
		n ++;
		ptr = ptr->next;
	}
	return (n);
}

static char	*join_key_value(char *key, char *value)
{
	int		i;
	int		len1;
	int		len2;
	char	*out;

	len1 = ft_strlen(key);
	len2 = ft_strlen(value);
	out = (char *) malloc((len1 + len2 + 2) * sizeof(char));
	if (!out)
		return (NULL);
	i = int_strcpy(out, 0, key);
	out[i ++] = '=';
	i = int_strcpy(out, i, value);
	out[i] = '\0';
	return (out);
}

static char	**get_env_array(t_env *env)
{
	int		i;
	int		n;
	t_env	*ptr;
	char	**out;

	n = get_total_env(env);
	out = (char **) malloc((n + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	i = -1;
	ptr = env;
	while (++ i < n)
	{
		out[i] = join_key_value(ptr->key, ptr->value);
		if (!out[i])
			return (free_strs(out), NULL);
		ptr = ptr->next;
	}
	out[i] = NULL;
	return (out);
}

static char	**get_path(char *value)
{
	int		i;
	char	*temp;
	char	**out;

	out = ft_split(value, ':');
	if (!out)
		return (NULL);
	i = -1;
	while (out[++ i])
	{
		temp = out[i];
		out[i] = ft_strjoin(out[i], "/");
		free(temp);
		if (!out[i])
			return (free_strs(out), NULL);
	}
	out[i] = NULL;
	return (out);
}

int	prepare_env_n_path(t_env *env, t_processor *p)
{
	t_env	*ptr;

	p->path = NULL;
	ptr = search_env(env, "PATH", 4);
	if (ptr)
	{
		p->path = get_path(ptr->value);
		if (!p->path)
			return (1);
	}
	p->env = get_env_array(env);
	if (!p->env)
		return (1);
	return (0);
}
