/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:59:42 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/02 12:21:30 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_print(t_shell *s, char **cmd)
{
	int		n;
	t_env	*ptr;

	n = get_number_arg(cmd, 1);
	if (n < 0)
		return (handle_error(s, 1), 0);
	if (n > 1)
		return (handle_error(s, 1), builtin_errmsg_arg(cmd[0]), 0);
	ptr = s->env;
	while (ptr)
	{
		write(1, ptr->key, ft_strlen(ptr->key));
		write(1, "=", 1);
		if (ptr->value)
			write(1, ptr->value, ft_strlen(ptr->value));
		write(1, "\n", 1);
		ptr = ptr->next;
	}
	return (0);
}

int	pwd_function(t_shell *s, char **cmd)
{
	int		n;
	int		fd;
	char	dir[4097];

	n = get_number_arg(cmd, 1);
	if (n < 0)
		return (handle_error(s, 1), 0);
	fd = 1;
	if (s->check)
		fd = s->check;
	if (s->root.pwd)
	{
		write(fd, s->root.pwd, ft_strlen(s->root.pwd));
		write(fd, "\n", 1);
		return (0);
	}
	ft_bzero(dir, 4097);
	getcwd(dir, 4096);
	write(fd, dir, ft_strlen(dir));
	write(fd, "\n", 1);
	return (0);
}

static void	check_first_arug_exit(t_shell *s, char **cmd)
{
	int	i;

	i = -1;
	while (cmd[1][++ i])
	{
		if (!ft_isdigit(cmd[1][i]))
		{
			write(2, "exit: numeric argument required\n", 32);
			s->status = 255;
			free_strs(cmd);
			free_all_exit(s, s->status);
		}
	}
}

int	exit_function(t_shell *s, char **cmd)
{
	int	max;

	max = 0;
	while (cmd[max])
		max ++;
	if (max > 1)
		check_first_arug_exit(s, cmd);
	if (max > 2)
	{
		write(2, "exit\nexit: too many arguments\n", 30);
		s->status = 1;
		return (0);
	}
	if (max == 2)
		s->status = ft_atoi(cmd[1]);
	write(1, "exit\n", 5);
	return (free_strs(cmd), free_all_exit(s, s->status), 1);
}

int	check_builtins(const t_proc *proc)
{
	if (!proc->cmd)
		return (0);
	if (!ft_strncmp(proc->cmd->token, "export", 7))
		return (1);
	else if (!ft_strncmp(proc->cmd->token, "unset", 6))
		return (2);
	else if (!ft_strncmp(proc->cmd->token, "exit", 5))
		return (3);
	else if (!ft_strncmp(proc->cmd->token, "cd", 3))
		return (4);
	else if (!ft_strncmp(proc->cmd->token, "pwd", 4))
		return (5);
	else if (!ft_strncmp(proc->cmd->token, "env", 4))
		return (6);
	else if (!ft_strncmp(proc->cmd->token, "echo", 5))
		return (7);
	return (0);
}
