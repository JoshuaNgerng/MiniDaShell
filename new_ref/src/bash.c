/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:30:13 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/21 16:42:25 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	bash(t_shell *s)
{
	int	i;
	int	type;

	i = 0;
	type= 0;
	while (s->input[i])
	{
		if (process_init(s, &i, &type))
			return (1);
		if (do_process(s))
			return (1);
		i = check_next_proc(s, s->input, i, type);
	}
	return (0);
}
