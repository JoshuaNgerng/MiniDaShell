/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:34:03 by jngerng           #+#    #+#             */
/*   Updated: 2024/01/31 09:49:46 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_transfer(t_shell *s, t_env *pwd, t_env *old, char *dir)
{
	if (old)
	{
		free(old->value);
		old->value = pwd->value;
	}
	free(s->root.pwd);
	s->root.pwd = ft_strdup(dir);
	pwd->value = ft_strdup(s->root.pwd);
	// printf("3) test oldpwd pwd root\n%s\n%s\n%s\n", old->value, pwd->value, s->root.pwd);
	if (!s->root.pwd || !pwd->value)
		return (1);
	return (0);
}

static int	cd_helper_root(t_shell *s)
{
	char	dir[4097];
	t_env	*ptr_pwd;
	t_env	*ptr_old;

	ft_bzero(dir, 4097);
	getcwd(dir, 4096);
	free(s->root.prompt);
	s->root.prompt = get_prompt(dir, s->root.root_msg);
	if (!s->root.prompt)
		return (errmsg_errno(0), 1);
	ptr_pwd = search_env(s->env, "PWD", 3);
	ptr_old = search_env(s->env, "OLDPWD", 6);
	// printf("2) test pwd oldpwd %p %p\n", ptr_pwd, ptr_old);
	if (ptr_pwd)
		return (env_transfer(s, ptr_pwd, ptr_old, dir));
	if (ptr_old)
		ptr_old->value = s->root.pwd;
	else
		free(s->root.pwd);
	s->root.pwd = ft_strdup(dir);
	if (!s->root.pwd)
		return (1);
	return (0);
}

int	check_oldpwd(t_shell *s)
{
	t_env	*new;

	s->root.change = 1;
	if (search_env(s->env, "OLDPWD", 7))
		return (0);
	new = make_env_node("OLDPWD=", 6);
	if (!new)
		return (handle_error(s, 137), 1);
	// printf("1) test new key value %s %s\n", new->key, new->value);
	// printf("1) test len key %ld\n", ft_strlen(new->key));
	env_list_addback(&s->env, new);
	return (0);
}

int	cd_chdir(char *dir, t_env *env)
{
	t_env	*ptr;

	if (!dir)
	{
		ptr = search_env(env, "HOME", 4);
		if (!ptr)
		{
			write(2, "cd: HOME not set\n", 17);
			return (1);
		}
		dir = ptr->value;
	}
	if (chdir(dir))
		return (errmsg_errno(0), 1);
	return (0);
}

int	cd_function(t_shell *s, char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i ++;
	if (i > 2)
	{
		write(2, "cd: too many arguments\n", 23);
		s->status = 1;
		return (0);
	}
	if (cd_chdir(cmd[1], s->env))
		return (handle_error(s, 1), 0);
	if (!s->root.change)
	{
		if (check_oldpwd(s))
			return (1);
	}
	if (cd_helper_root(s))
		return (handle_error(s, 137), 1);
	return (0);
}