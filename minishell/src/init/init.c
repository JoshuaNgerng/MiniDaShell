/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:35:47 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/01 06:16:14 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_builtins(t_shell *s, char **av)
{
	s->builtin[0] = export;
	s->builtin[1] = unset;
	s->builtin[2] = exit_function;
	s->builtin[3] = cd_function;
	s->builtin[4] = pwd_function;
	s->builtin[5] = env_print;
	errmsg_name(av[0]);
}

int	shell_init(t_shell *s, char **av, char **env)
{
	char	dir[4097];

	errno = 0;
	s->root.root_msg = root_init(env);
	if (!s->root.root_msg)
		return (1);
	ft_bzero(dir, 4097);
	if (!getcwd(dir, 4096))
		return (errmsg_errno(3), free(s->root.root_msg), 1);
	s->root.prompt = get_prompt(dir, s->root.root_msg);
	if (!s->root.prompt)
		return (free(s->root.root_msg), 1);
	s->env = env_list_init(env);
	if (!s->env)
		return (free(s->root.root_msg), 1);
	s->root.pwd = ft_strdup(dir);
	if (!s->root.pwd)
		return (free_env_list(s->env), free(s->root.root_msg), 1);
	s->processor.stdout_ = 1;
	return (set_builtins(s, av), 0);
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
