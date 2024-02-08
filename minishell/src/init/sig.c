/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:35:47 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/07 12:08:14 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int signum)
{
	(void) signum;
	g_ctrl_c = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signal_heredoc(int signum)
{
	(void) signum;
	g_ctrl_c = 1;
	write(1, "\n", 1);
}

void	handle_sig_child(int signum)
{
	if (signum == SIGINT)
	{
		g_ctrl_c = 130;
		write(1, "^C\n", 3);
	}
	if (signum == SIGQUIT)
	{
		g_ctrl_c = 131;
		write(1, "^\\Quit: 3\n", 10);
	}
}

void	handle_sig_limbo(int signum)
{
	if (signum == SIGINT)
		write(1, "^C\n", 3);
	if (signum == SIGQUIT)
		write(1, "^\\", 2);
}

void	reassign_sig(int check, void (*f)(int))
{
	if (check)
		return ;
	signal(SIGINT, f);
	signal(SIGQUIT, f);
}
