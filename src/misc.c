/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:56:31 by mukhairu          #+#    #+#             */
/*   Updated: 2023/11/09 16:52:04 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	chk_dbl(char *str, char c)
{
	int	i;
	int	cnt;

	i = -1;
	cnt = 0;
	while (str[i++])
	{
		if (str[i] == c)
			cnt++;
	}
	if (cnt > 1)
		return (1);
	return (0);
}
