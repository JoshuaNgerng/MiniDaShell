/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:12:27 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/07 23:03:23 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env(char **env, char *var, int len)
{
	char	**buffer;

	buffer = env;
	while (*buffer)
	{
		if (!ft_strncmp(*buffer, var, len))
			return (*(buffer) + len + 1);
		buffer ++;
	}
	return (NULL);
}

static void	search_env_root(char **env, t_root_ptr *r)
{
	r->tmp1 = get_env(env, "LOGNAME", 7);
	r->tmp2 = get_env(env, "NAME", 4);
	if (!r->tmp2)
		r->tmp2 = get_env(env, "USER", 4);
	if (!r->tmp1)
		r->tmp1 = "42";
	if (!r->tmp2)
		r->tmp2 = "USER";
	r->len1 = ft_strlen(r->tmp1);
	r->len2 = ft_strlen(r->tmp2);
}

static char	*root_init(char **env)
{
	int			i;
	char		*out;
	t_root_ptr	r;

	search_env_root(env, &r);
	out = (char *) malloc ((r.len1 + r.len2 + 14) * sizeof(char));
	if (!out)
		return (NULL);
	ft_strlcpy(out, GREEN, 8);
	ft_strlcpy(&out[7], r.tmp1, r.len1 + 1);
	i = 7 + r.len1;
	out[i ++] = '@';
	ft_strlcpy(&out[i], r.tmp2, r.len2 + 1);
	i += r.len2;
	ft_strlcpy(&out[i], RESET, 5);
	i += 4;
	out[i] = ':';
	out[++ i] = '\0';
	return (out);
}

static void	set_builtins(t_shell *s)
{
	s->builtin[0] = export;
	s->builtin[1] = unset;
	s->builtin[2] = exit_function;
	s->builtin[3] = cd_function;
	s->builtin[4] = pwd_function;
	s->builtin[5] = env_print;
	s->builtin[6] = echo_function;
}

int	shell_init(t_shell *s, char **av, char **env)
{
	char	dir[4097];

	errno = 0;
	errmsg_name(av[0]);
	is_name(av[0]);
	if (setup_signal(s))
		return (1);
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
	return (set_builtins(s), 0);
}
