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

int	setup_signal(t_shell *s)
{
	if (signal(SIGINT, handle_signal) == SIG_ERR || \
		signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (errmsg_errno(13), 1);
	if (tcgetattr(STDIN_FILENO, &s->termios_) == -1)
		return (errmsg_errno(22), 1);
	s->termios_.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &s->termios_) == -1)
		return (errmsg_errno(23), 1);
	return (0);
}

void	handle_signal(int signum)
{
	(void) signum;
	g_ctrl_c = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
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
