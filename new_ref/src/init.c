/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:21:56 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/09 10:57:28 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(char **env)
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

char	*root_init(char **env)
{
	int		i;
	int		len1;
	int		len2;
	char	*out;
	char	*tmp1;
	char	*tmp2;

	tmp1 = get_env(env, "LOGNAME", 7);
	tmp2 = get_env(env, "NAME", 4);
	len1 = strlen(tmp1);
	len2 = strlen(tmp2);
	out = (char *) malloc ((len1 + len2 + 14) * sizeof(char));
	if (!out)
		return (NULL);
	strncpy(out, GREEN, 7);
	strncpy(&out[7], tmp1, len1);
	i = 7 + len1;
	out[i ++] = '@';
	strncpy(&out[i], tmp2, len2);
	i += len2;
	strncpy(&out[i], RESET, 4);
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
		return (free(root), NULL);
	ft_strncpy(out, root, len_root);
	ft_strncpy(&out[len_root], BLUE, 7);
	i = len_root + 7;
	ft_strncpy(&out[i], direc, len);
	i += len;
	ft_strncpy(&out[i], RESET, 4);
	i += 4;
	out[i ++] = '$';
	out[i ++] = ' ';
	out[i] = '\0';
	return (out);
}

int	msg_init(prompt *msg)
{
	if (!getcwd(msg->directory, 4096))
		return (errmsg_errno(3), 1);
	msg->prompt = get_prompt(msg->directory, msg->root);
	if (!msg->prompt)
		return (1);
	msg->change = 0;
	return (0);
}

int	shell_init(t_shell *s, char **env)
{
	static t_shell	zero_shell;

	*s = zero_shell;
	s->env = env;
	s->path = get_path(env);
	if (!s->path)
		return (1);
	s->root.root_msg = root_init(env);
	if (!s->root.root_msg)
		return (free(s->path), 1)
	if (msg_init(&s->msg))
		return (free(s->msg.root), free(s->path), 1);
	return (0);
}
