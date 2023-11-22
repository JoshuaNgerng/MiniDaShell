/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:30:13 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/22 11:30:25 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	subshell(t_shell *s)
{
	return (0);
}

int	check_subshell()
{
	;
}

// loop brackets with subshell
// need to rewrite token buffer
// check type for brackets
// open subshell
// if its logical operator or end
// do_proc in main
// skip skip till end brack or skip not needed proc
int	bash(t_shell *s)
{
	int	i;
	int	type;

	i = 0;
	type= 0;
	while (s->input[i])
	{
		if (check_subshell())
			return (1);
		if (process_init(s, &i, &type))
			return (1);
		printf("loop test %d\n", type);
		printf("testing i(%d) type(%d)\n", i, type);
		dev_print_data(s->process_section.proc);
		free_process_section(s);
		// if (do_process(s))
		// 	return (1);
		// i = check_next_proc(s, s->input, i, type);
	}
	return (0);
}
