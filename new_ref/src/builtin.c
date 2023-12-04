/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:46:26 by jngerng           #+#    #+#             */
/*   Updated: 2023/12/04 22:02:17 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_function(t_shell *s, char **cmd)
{
	int	i;

	i = -1;
	while (cmd[i])
		i ++;
	if (i > 2)
	{
		write(2, "exit: too many arguments\n", 25);
		s->status = 1;
		return ;
	}
	i = -1;
	while (cmd[1][++ i])
	{
		if (!ft_isdigit(cmd[1][i]))
		{
			write(2, "exit: numeric argument required\n", 32);
			s->status = 1;
		}
	}
	free_strs(cmd);
	free_all_exit(s, s->status);
}

int	make_cmd_special_process(t_shell *s, t_proc *proc, int check)
{
	int		ext;
	char	**cmd;

	cmd = get_cmd_array(proc->cmd);
	if (!cmd)
		return (handle_error(s, 137), 1);
	ext = 0;
	if (check == 1)
		ext = export(s, cmd);
	else if (check == 2)
		ext = unset(s, cmd);
	else if (check == 3)
		exit_function(s, cmd);
	return (free_strs(cmd), ext);
}

int	check_special_process(t_shell *s, t_processor *p, t_proc *proc)
{
	int	check;

	check = 0;
	if (!ft_strncmp(proc->cmd->token, "export", 7))
		check = 1;
	if (!ft_strncmp(proc->cmd->token, "unset", 6))
		check = 2;
	if (!ft_strncmp(proc->cmd->token, "exit", 5))
		check = 3;
	if (check)
		return (make_cmd_special_process(s, proc, check));
	if (process_child(s, p, proc))
		return (1);
	waitpid(p->pid[0], &s->status, 0);
	return (0);
}
