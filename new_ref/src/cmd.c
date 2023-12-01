/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:25:05 by jngerng           #+#    #+#             */
/*   Updated: 2023/12/01 16:50:14 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_cmd_array(t_token *cmd)
{
	int		i;
	int		len;
	char	**out;
	t_token	*ptr;

	len = 1;
	ptr = cmd;
	while (ptr)
	{
		len ++;
		ptr = ptr->next;
	}
	out = (char **) malloc(len * sizeof(char));
	if (!out)
		return (errmsg_errno(11), NULL);
	ptr = cmd;
	i = -1;
	while (++ i < len)
	{
		out[i] = ptr->token;
		ptr->token = NULL;
		ptr = ptr->next;
	}
	out[i] = NULL;
	return (out);
}

static char	*find_shell_cmd(char **path, char *cmd, int *ext_code)
{
	int		i;
	char	*out;

	i = -1;
	out = NULL;
	while (path[++ i])
	{
		out = ft_strjoin(path[i], cmd);
		if (!out)
		{
			*ext_code = 137;
			return (NULL);
		}
		if (!access(out, F_OK | X_OK))
			return (out);
		free(out);
		out = NULL;
	}
	*ext_code = 127;
	return (out);
}

int	find_cmd(char **path, char **path_cmd, char *cmd, int *ext_code)
{
	char	*find_cmd;

	find_cmd = find_shell_cmd(path, cmd, ext_code);
	if (!find_cmd)
	{
		if (errno)
			return (errmsg_errno(10), 1);
		if (!(ft_strrchr(cmd, '/') && !access(cmd, F_OK | X_OK)))
			return (sp_errmsg(3, cmd), 1);
		*ext_code = 0;
		*path_cmd = ft_strdup(cmd);
		if (!(*path_cmd))
		{
			*ext_code = 137;
			return (errmsg_errno(10), 1);
		}
	}
	*path_cmd = find_cmd;
	return (0);
}
