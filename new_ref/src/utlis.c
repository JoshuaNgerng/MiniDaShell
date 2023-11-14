/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:16:28 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/10 17:57:33 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_checkset(char const s, char const *set)
{
	while (*set)
	{
		if (*set == s)
			return (1);
		set ++;
	}
	return (0);
}

int	pass_space(char *input, int start)
{
	int	end;

	end = start;
	while (input[end] && input[end] == ' ')
		end ++;
	return (end);
}

char	*get_env(char **env, char *var, int len)
{
	char	**buffer;

	buffer = env;
	while (buffer)
	{
		if (!ft_strncmp(*buffer, var, len))
			return (*(buffer) + len + 1);
		buffer ++;
	}
	return (NULL);
}

char	*get_input(t_shell *s, char *prompt)
{
	int		i;
	char	*r;

	while (1)
	{
		r = readline(prompt);
		if (!r)
		{
			if (errno)
				return (handle_error(s, 137), errmsg_errno(2), NULL);
			return (NULL);
		}
		i = -1;
		while (r[++ i])
			if (r[i] != ' ')
				break ;
		if (r[i])
			break ;
		free(r);
	}
	return (r);
}

int	int_strchr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c)
		i ++;
	if (s[i] != c)
		return (-1);
	return (i);
}