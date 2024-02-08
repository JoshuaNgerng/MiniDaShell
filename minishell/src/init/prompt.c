/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:43:46 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/07 09:44:27 by jngerng          ###   ########.fr       */
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

char	*get_prompt(char *direc, char *root)
{
	int		len;
	int		len_root;
	int		i;
	char	*out;
	char	*ptr;

	ptr = ft_strrchr(direc, '/');
	len = ft_strlen(ptr) - 1;
	len_root = ft_strlen(root);
	out = (char *) malloc ((len + len_root + 14) * sizeof(char));
	if (!out)
		return (free(root), NULL);
	ft_strlcpy(out, root, len_root + 1);
	ft_strlcpy(&out[len_root], BLUE, 8);
	i = len_root + 7;
	ft_strlcpy(&out[i], &ptr[1], len + 1);
	i += len;
	ft_strlcpy(&out[i], RESET, 5);
	i += 4;
	out[i ++] = '$';
	out[i ++] = ' ';
	out[i] = '\0';
	return (out);
}
