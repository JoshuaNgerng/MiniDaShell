/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 02:00:35 by jngerng           #+#    #+#             */
/*   Updated: 2023/12/01 16:36:46 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_helper(t_processor *p, int *fd_in, int *fd_out, int check)
{
	if (check == here_doc)
	{
		if (*fd_in > 0)
			close(*fd_in);
		*fd_in = p->here_doc_pipe[p->index_h * 2 + 1];
	}
	if (p->pipe)
	{
		if (!(*fd_in) && p->index_p > 0)
			*fd_in = p->pipe[(p->index_p - 1) * 2 + 1];
		if (*fd_out < 2 && p->index_p < p->pipe_num)
			*fd_out = p->pipe[p->index_p * 2];
	}
}

int	dup_stdin_stdout(t_shell *s, t_processor *p, t_proc *proc)
{
	int	fd_in;
	int	fd_out;

	(void) s;
	fd_in = cycle_input_files(proc->f_read);
	fd_out = cycle_output_files(proc->f_out);
	if (fd_in < 0 || fd_out < 0)
		return (1);
	dup_helper(p, &fd_in, &fd_out, proc->in);
	printf("dup stdin (%d), stdout(%d) \n", fd_in, fd_out);
	// if (dup2(fd_in, 0) || dup2(fd_out, 1))
		// return (1);
	close_pipes(p->pipe, p->pipe_num);
	close_pipes(p->here_doc_pipe, p->here_doc_num);
	return (0);
}

void	free_child_exit(t_shell *s, char **cmd, char *path_cmd, int ext_code)
{
	free_all(s);
	free_strs(cmd);
	if (path_cmd)
		free(path_cmd);
	exit(ext_code);
}

void	child_process(t_shell *s, t_processor *p, t_proc *proc)
{
	int		ext_code;
	char	**cmd;
	char	*path_cmd;

	cmd = get_cmd_array(proc->cmd);
	if (!cmd)
		printf("free_exit with ext_code 137\n");
	path_cmd = NULL;
	if (find_cmd(s->path, &path_cmd, cmd[0], &ext_code))
		printf("cmd error (%d)\n", ext_code);
	if (dup_stdin_stdout(s, p, proc))
		printf("dup error free exit\n");
	printf("execve\n");
	printf("path: %s\n", path_cmd);
	dev_print_strs(cmd);
	printf("if execve failed ext_code 1\n");
}

int	process_child(t_shell *s, t_processor *p, t_proc *hold)
{
	// int	pid;

	printf("make child process\n");
	// pid = fork();
	// if (pid < 0)
	// 	return (1);
	// if (!pid)
	child_process(s, p, hold);
	printf("back in main\n");
	//else
	printf("assign pid to main struct\n");
	if (hold->here_doc)
	{
		if (hold->here_doc)
			p->index_h ++;
	}
	return (0);
}