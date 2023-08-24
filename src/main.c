/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 04:53:00 by jngerng           #+#    #+#             */
/*   Updated: 2023/08/18 04:53:00 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
user interface can add more stuff later
*/
char	*get_input(char *prompt)
{
	char	*r;

	r = readline(prompt);
	while (!r)
		r = readline(prompt);
	while (!r[0])
		r = readline(prompt);
	if (r && r[0])
		add_history(r);
	return (r);
}

int	main(void)
{
	char	*input;
	t_shell	shell;

	shell = (t_shell){0, 0, 0, 0};
	input = get_input("test input: ");
	if (!input)
		return (sp_errmsg(0, NULL, errno), 1);
	while (ft_strncmp(&input[0], "exit", 5))
	{
		if (parse_info(input, &shell))
			return (free(input), sp_errmsg(1, NULL, errno), 1);
		// do_bash(&shell);
		// wait_bash(&shell);
		print_info(shell);
		free_all(&shell);
		free(input);
		// system("leaks minishell");
		input = get_input("test input: ");
		if (!input)
			return (free_all(&shell), sp_errmsg(0, NULL, errno), 1);
	}
	return (free(input), free_all(&shell), 0);
}
