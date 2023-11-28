/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:42:42 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/28 14:03:27 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pid_pfd_init(t_block *b)
{
	b->pid = (int *) malloc(b->num * sizeof(int));
	if (!b->pid)
		return (1);
	b->pfd = (int *) malloc((b->num + b->add) * sizeof(int));
	if (!b->pfd)
		return (1);
	return (0);
}

static void	transfer_token_proc(t_proc *new, t_buffer buffer)
{
	int		i;
	t_token	*ptr;

	new->here_doc = buffer.here_doc.head;
	new->f_read = buffer.read.head;
	new->f_out = buffer.out.head;
	if (!new->cmd)
	{
		free_tokens(buffer.cmd.head);
		return ;
	}
	i = -1;
	while (++ i < buffer.size)
	{
		new->cmd[i] = buffer.cmd.head->token;
		ptr = buffer.cmd.head;
		free(ptr);
		buffer.cmd.head = buffer.cmd.head->next;
	}
	new->cmd[i] = NULL;
}

static int	get_process_node(t_shell *s, t_proc **ptr, t_block *b, t_token *t)
{
	t_token		*temp;
	t_proc		*new;
	t_buffer	buffer;

	buffer = (t_buffer){0, (t_ptr){0, 0}, \
			(t_ptr){0, 0}, (t_ptr){0, 0}, (t_ptr){0, 0}};
	*ptr = NULL;
	new = (t_proc *) malloc(sizeof(t_proc));
	if (!new)
		return (handle_error(s, 137), errmsg_errno(5), 1);
	b->num ++;
	while (t)
	{
		temp = t;
		t = t->next;
		transfer_token_buffer(new, &buffer, b, temp);
	}
	if (expand_tokens(s, &buffer))
		return (1);
	new->cmd = (char **) malloc((buffer.size + 1) * sizeof(char *));
	transfer_token_proc(new, buffer);
	if (!new->cmd)
		return (handle_error(s, 137), free_process(new), 1);
	*ptr = new;
	return (0);
}

int	process_init(t_shell *s, int *i, int *type)
{
	t_token	*buffer;
	t_proc	*ptr;

	if (tokenize_input(s, &buffer, i, type))
		return (1);
	if (!buffer)
		return (0);
	ptr = s->process_section.proc;
	if (get_process_node(s, &ptr, &s->process_section, buffer))
		return (1);
	while (s->input[*i] && !(*type & (LOGIC | BRACKETS)))
	{
		if (tokenize_input(s, &buffer, i, type))
			return (free_process_section(s), 1);
		if (get_process_node(s, &ptr->next, &s->process_section, buffer))
			return (free_process_section(s), 1);
		ptr = ptr->next;
	}
	ptr->next = NULL;
	if (pid_pfd_init(&s->process_section))
		return (handle_error(s, 137), free_process_section(s), 1);
	return (0);
}
