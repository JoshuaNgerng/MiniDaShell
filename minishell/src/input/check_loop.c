/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:24:22 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/07 22:59:07 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_new_prev_tokens(int new, int prev)
{
	if (prev & FILES && new)
		return (errmsg_token(new), -1);
	else if (prev == end_b && (new && !(new & LOGIC)))
		return (errmsg_token(new), -1);
	else if (new & OPERATORS && prev == start_b)
		return (errmsg_token(new), -1);
	else if (new == _pipe && prev > 0)
		return (errmsg_token(new), -1);
	else if (new & LOGIC && prev && prev != end_b)
		return (errmsg_token(new), -1);
	else if (new == start_b && !(prev & LOGIC))
		return (errmsg_token(new), -1);
	else if (new == end_b && (prev && prev != end_b))
		return (errmsg_token(new), -1);
	return (0);
}
