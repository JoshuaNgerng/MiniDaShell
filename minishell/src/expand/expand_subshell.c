/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:25:58 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/01 08:27:13 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	finish_expand_subshell(t_token *new, int fd, t_ptr *buffer, t_expand *e)
{
	e->s->status = WEXITSTATUS(e->s->status);
	new->token = read_from_pipe(fd);
	close(fd);
	new->next = NULL;
	e->str[e->i] = '$' * -1;
	if (new->token)
		e->len += ft_strlen(new->token);
	return (transfer_token_ptr(buffer, new), 0);
}

t_proc	*make_subshell_node(char *str, int i, int *ptr)
{
	int		j;
	t_proc	*new;

	new = (t_proc *) malloc(sizeof(t_proc));
	if (!new)
		return (NULL);
	new->cmd = (t_token *) malloc(sizeof(t_token));
	if (!new->cmd)
		return (free(new), NULL);
	j = i;
	while (str[j] && str[j] != ')')
		j ++;
	*ptr = j - i;
	new->cmd->token = ft_substr(str, i + 1, *ptr);
	if (!new->cmd->token)
		return (free(new->cmd), free(new), NULL);
	new->cmd->next = NULL;
	new->f_out = NULL;
	new->f_read = NULL;
	new->here_doc = NULL;
	new->next = NULL;
	new->in = 0;
	return (new);
}

static void	fork_error(int pipes[2], int *ptr, int ref, t_proc *temp)
{
	close(pipes[0]);
	close(pipes[1]);
	*ptr = ref;
	free_process(temp);
}

int	expand_subshell(t_token *new, t_ptr *buffer, t_expand *e)
{
	int		pid;
	int		ref;
	int		pipe_fd[2];
	t_proc	*temp;

	temp = make_subshell_node(e->str, e->i, &new->type);
	if (!temp)
		return (free(new), 1);
	if (pipe(pipe_fd))
		return (free_process(temp), free(new), errmsg_errno(20), 1);
	ref = e->s->processor.stdout_;
	e->s->processor.stdout_ = pipe_fd[1];
	pid = fork();
	if (pid < 0)
		return (fork_error(pipe_fd, &e->s->processor.stdout_, ref, temp),
			errmsg_errno(21), free(new), 1);
	if (!pid)
		subshell(e->s, &e->s->processor, temp);
	free_process(temp);
	close(pipe_fd[1]);
	e->s->processor.stdout_ = ref;
	waitpid(pid, &e->s->status, 0);
	return (finish_expand_subshell(new, pipe_fd[0], buffer, e));
}
