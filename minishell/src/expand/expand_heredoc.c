/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:40:49 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/02 10:52:30 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_len_here_doc(const char *src)
{
	int	i;
	int	j;
	int	quo;

	i = -1;
	j = 0;
	quo = 0;
	while (src[++ i])
	{
		if (src[i] == '\'' || src[i] == '"')
		{
			if (!quo)
			{
				quo = src[i];
				j ++;
			}
			else
			{
				quo = read_quo(src[i], quo);
				if (!quo)
					j ++;
			}
		}
	}
	return (i - j);
}

static void	copy_over_here_doc(char *dst, const char *src)
{
	int	i;
	int	j;
	int	quo;

	i = -1;
	j = 0;
	quo = 0;
	while (src[++ i])
	{
		if (src[i] == '\'' || src[i] == '"')
		{
			if (!quo)
				quo = src[i];
			else
			{
				quo = read_quo(src[i], quo);
				if (quo)
					dst[j ++] = src[i];
			}
		}
		else
			dst[j ++] = src[i];
	}
	dst[j] = '\0';
}

int	expand_here_doc(t_shell *s, t_token *t)
{
	int		len;
	char	*out;

	len = get_len_here_doc(t->token);
	out = (char *) malloc((len + 1) * sizeof(char));
	if (!out)
		return (handle_error(s, 137), 1);
	copy_over_here_doc(out, t->token);
	free(t->token);
	t->token = out;
	return (0);
}
