/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:25:58 by jngerng           #+#    #+#             */
/*   Updated: 2024/01/30 12:21:25 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_buffer(char *out, char *buffer, int r)
{
	char	*temp;

	if (r >= 0 && r <= BUFFER_SIZE)
		buffer[r] = '\0';
	else
		return (NULL);
	if (!out && !*buffer)
		return (NULL);
	if (!out)
		out = ft_strjoin(buffer, "");
	else
	{
		temp = out;
		out = ft_strjoin(out, buffer);
		free(temp);
	}
	return (out);
}

char	*read_from_pipe(int fd)
{
	int		r;
	char	*out;
	char	*buffer;

	buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	r = read(fd, buffer, BUFFER_SIZE);
	while (r > 0)
	{
		out = join_buffer(out, buffer, r);
		if (!out)
			return (free(buffer), NULL);
		r = read(fd, buffer, BUFFER_SIZE);
	}
	if (r == -1)
		return (free(buffer), NULL);
	return (free(buffer), out);
}

int	finish_expand_subshell(t_token *new, int fd, t_ptr *buffer)
{
	new->token = read_from_pipe(fd);
	close(fd);
	if (!new->token)
		return (free(new), 1);
	return (transfer_token_ptr(buffer, new), 0);
}

t_proc	*make_subshell_node(char *str, int i)
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
	new->cmd->token = ft_substr(str, i + 1, j - i);
	if (!new->cmd->token)
		return (free(new->cmd), free(new), NULL);
	printf("testing new cmd:%s\n", new->cmd->token);
	new->cmd->next = NULL;
	new->f_out = NULL;
	new->f_read = NULL;
	new->here_doc = NULL;
	new->next = NULL;
	new->in = 0;
	return (new);
}

int	expand_subshell(t_token *new, t_ptr *buffer, t_expand *e)
{
	int		pid;
	int		ref;
	int		pipe_fd[2];
	t_proc	*temp;

	printf("test expand subshell\n");
	temp = make_subshell_node(e->str,e->i);
	if (!temp)
		return (free(new), 1);
	if (pipe(pipe_fd))
		return (free_process(temp), free(new), 1); //ermsg
	printf("test pipe %d %d\n", pipe_fd[0], pipe_fd[1]);
	ref = e->s->processor.stdout_;
	e->s->processor.stdout_ = pipe_fd[1];
	pid = fork();
	if (pid < 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		e->s->processor.stdout_ = ref;
		return (free_process(temp), free(new), 1);
	}
	if (!pid)
		subshell(e->s, &e->s->processor, temp);
	free_process(temp);
	close(pipe_fd[1]);
	waitpid(pid, &e->s->status, 0);
	e->s->status = WEXITSTATUS(e->s->status);
	e->s->processor.stdout_ = ref;
	return (finish_expand_subshell(new, pipe_fd[0], buffer));
}
