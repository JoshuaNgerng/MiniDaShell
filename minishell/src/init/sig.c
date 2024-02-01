/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:35:47 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/01 15:50:09 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_signal(t_shell *s)
{
	if (signal(SIGINT, handle_signal) == SIG_ERR || \
		signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (errmsg_errno(13), 1);
	if (tcgetattr(0, &s->termios_) == -1)
		return (errmsg_errno(22), 1);
	s->termios_.c_lflag &= ~ECHOCTL;
	if (tcsetattr(1, TCSANOW, &s->termios_) == -1)
		return (errmsg_errno(23), 1);
	return (0);
}

void	handle_signal(int signum)
{
	if (signum == SIGINT)
	{
		g_ctrl_c = 1;
		write(1, "\n", 1);
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
