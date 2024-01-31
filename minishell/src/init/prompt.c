/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:12:27 by jngerng           #+#    #+#             */
/*   Updated: 2024/01/31 17:55:53 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	search_env_root(char **env, t_root_ptr *r)
{
	r->tmp1 = get_env(env, "LOGNAME", 7);
	r->tmp2 = get_env(env, "NAME", 4);
	if (!r->tmp2)
		r->tmp2 = get_env(env, "USER", 4);
	r->len1 = ft_strlen(r->tmp1);
	r->len2 = ft_strlen(r->tmp2);
}

char	*root_init(char **env)
{
	int			i;
	char		*out;
	t_root_ptr	r;

	search_env_root(env, &r);
	out = (char *) malloc ((r.len1 + r.len2 + 14) * sizeof(char));
	if (!out)
		return (NULL);
	ft_strlcpy(out, GREEN, 8);
	ft_strlcpy(&out[7], r.tmp1, r.len1 + 1);
	i = 7 + r.len1;
	out[i ++] = '@';
	ft_strlcpy(&out[i], r.tmp2, r.len2 + 1);
	i += r.len2;
	ft_strlcpy(&out[i], RESET, 5);
	i += 4;
	out[i] = ':';
	out[++ i] = '\0';
	return (out);
}

char	*get_prompt(char *direc, char *root)
{
	int		len;
	int		len_root;
	int		i;
	char	*out;

	len = ft_strlen(direc);
	len_root = ft_strlen(root);
	out = (char *) malloc ((len + len_root + 14) * sizeof(char));
	if (!out)
		return (free(root), NULL);
	ft_strlcpy(out, root, len_root + 1);
	ft_strlcpy(&out[len_root], BLUE, 8);
	i = len_root + 7;
	ft_strlcpy(&out[i], direc, len + 1);
	i += len;
	ft_strlcpy(&out[i], RESET, 5);
	i += 4;
	out[i ++] = '$';
	out[i ++] = ' ';
	out[i] = '\0';
	return (out);
}
