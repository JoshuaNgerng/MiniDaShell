/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:24:22 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/01 11:36:05 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_inside_loop_helper(int new, int prev)
{
	if (prev & FILES && new)
		return (errmsg_token(new), -1);
	else if (new & OPERATORS && prev == start_b)
		return (errmsg_token(new), -1);
	else if (new == _pipe && prev > 0)
		return (errmsg_token(new), -1);
	else if (new & LOGIC && prev && prev != end_b)
		return (errmsg_token(new), -1);
	else if (new & start_b && !(prev & (OPERATORS | start_b)))
		return (errmsg_token(new), -1);
	else if (new & end_b && (prev && prev != end_b))
		return (errmsg_token(new), -1);
	return (0);
}

int	check_inside_loop(char *input, int i, int *prev, int *brac)
{
	int	j;
	int	new;

	new = 0;
	i = pass_space(input, i);
	if (!input[i])
		return (i);
	j = get_new_token(input, i, &new, brac);
	if (j < 0)
		return (-1);
	if (!new && *prev == end_b)
		return (errmsg_token(*prev), -1);
	if (check_inside_loop_helper(new, *prev))
		return (-1);
	*prev = new;
	return (j);
}
