/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 02:22:13 by jngerng           #+#    #+#             */
/*   Updated: 2023/09/14 16:07:45 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_cmd(char *cmd, char **paths)
{
	char	*out;
	char	**buffer;

	if (!cmd)
		return (NULL);
	buffer = paths;
	while (*buffer)
	{
		out = ft_strjoin(*buffer, cmd);
		if (!out)
			return (sp_errmsg(3, cmd), NULL);
		if (!access(out, F_OK | X_OK))
			return (out);
		free(out);
		buffer ++;
	}
	return (NULL);
}

char	*find_path_cmd(char *cmd)
{
	int	i;
	int	len;
	
	if (access(cmd, F_OK | X_OK))
		return (NULL);
	len = ft_strlen(cmd);
	i = 0;
	while (++ i <= len)
		if (cmd[len - i] == '/')
			break ;
	return (ft_substr(cmd, len - i, i));
}
// add checking errno
char	*check_valid_cmd(char **cmd, char **path)
{
	int		l;
	char	*out;
	char	*tmp;

	l = ft_strlen(cmd[0]);
	if (!ft_strncmp(cmd[0], "export", l))
		return (NULL); 
	out = find_cmd(cmd[0], path);
	if (!out && !errno)
	{
		out = find_path_cmd(cmd[0]);
		if (!out)
		{
			if (errno == 12)
				return (errmsg_errno(6), NULL);
			return (sp_errmsg(3, cmd[0]), NULL);
		}
		tmp = cmd[0];
		cmd[0] = out;
		out = tmp;
	}
	return (out);
}
