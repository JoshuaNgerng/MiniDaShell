/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:43:46 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/07 09:44:27 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt(char *direc, char *root)
{
	int		len;
	int		len_root;
	int		i;
	char	*out;
	char	*ptr;

	ptr = ft_strrchr(direc, '/');
	len = ft_strlen(ptr) - 1;
	len_root = ft_strlen(root);
	out = (char *) malloc ((len + len_root + 14) * sizeof(char));
	if (!out)
		return (free(root), NULL);
	ft_strlcpy(out, root, len_root + 1);
	ft_strlcpy(&out[len_root], BLUE, 8);
	i = len_root + 7;
	ft_strlcpy(&out[i], &ptr[1], len + 1);
	i += len;
	ft_strlcpy(&out[i], RESET, 5);
	i += 4;
	out[i ++] = '$';
	out[i ++] = ' ';
	out[i] = '\0';
	return (out);
}
