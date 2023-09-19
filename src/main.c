/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:40:53 by mukhairu          #+#    #+#             */
/*   Updated: 2023/08/23 18:29:04 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(void)
{
	char	*freer;
	// signal(SIGQUIT, SIG_IGN);
	printf("Hello, welcome to MINIDASHELL!\n");
	if (signal(SIGINT, handle_signal) == SIG_ERR
		&& signal(SIGQUIT, handle_signal) == SIG_ERR)
	{
		perror("Error! Signal handler!\n");
		return (1);
	}
	freer = readline("MiniDaShell %");
	while (freer && ft_strncmp(freer, "exit", 5))
	{
		free(freer);
		freer = readline("MiniDaShell %");
	}
	if (!freer)
		free(freer);
	printf("exit\n");
	return (0);
}
