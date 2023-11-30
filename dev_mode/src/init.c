/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:21:56 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/30 22:26:48 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_path(char **env)
{
	char	**out;
	char	**buffer;
	char	*temp;

	out = ft_split(get_env(env, "PATH", 4), ':');
	if (!out)
		return (NULL);
	buffer = out;
	while (*buffer)
	{
		temp = *buffer;
		*buffer = ft_strjoin(*buffer, "/");
		if (!(*buffer))
		{
			*buffer = temp;
			return (free_strs(out), NULL);
		}
		free(temp);
		buffer ++;
	}
	return (out);
}

static char	*root_init(char **env)
{
	int		i;
	int		len1;
	int		len2;
	char	*out;
	char	*tmp1;
	char	*tmp2;

	tmp1 = get_env(env, "LOGNAME", 7);
	tmp2 = get_env(env, "USER", 4);
	len1 = strlen(tmp1);
	len2 = strlen(tmp2);
	out = (char *) malloc ((len1 + len2 + 14) * sizeof(char));
	if (!out)
		return (NULL);
	ft_strlcpy(out, GREEN, 7);
	ft_strlcpy(&out[7], tmp1, len1);
	i = 7 + len1;
	out[i ++] = '@';
	ft_strlcpy(&out[i], tmp2, len2);
	i += len2;
	ft_strlcpy(&out[i], RESET, 4);
	i += 4;
	out[i] = ':';
	out[++ i] = '\0';
	return (out);
}

static char	*get_prompt(char *direc, char *root)
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

int	shell_init(t_shell *s, char **env)
{
	errno = 0;
	s->env_ptr = env;
	s->path = get_path(env);
	if (!s->path)
		return (1);
	s->root.root_msg = root_init(env);
	if (!s->root.root_msg)
		return (free(s->path), 1);
	if (!getcwd(s->root.directory, 4096))
		return (errmsg_errno(3), free(s->root.root_msg), free(s->path), 1);
	s->root.prompt = get_prompt(s->root.directory, s->root.root_msg);
	if (!s->root.prompt)
		return (free(s->root.root_msg), free(s->path), 1);
	s->env = env_list_init(env);
	if (!s->env)
		return (free(s->root.root_msg), free(s->path), 1);
	return (0);
}
