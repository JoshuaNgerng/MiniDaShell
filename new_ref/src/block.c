/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:36:10 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/09 13:29:35 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_block_head(t_block_ptr *b, t_shell *s, t_loop *loop)
{
	b->head = (t_block *) malloc (sizeof(t_block));
	if (!b->head)
		return (errmsg_errno(), 1);
	if (!tokenize_input(b->head, s, loop))
		return (1);
	b->tail = b->head;
	b->tail->next = NULL;
	return (0);
}

int	get_block(t_block_ptr *b, t_shell *s, t_loop *loop)
{
	t_block	*ptr;
	t_block	*new;

	if (!b->head)
	{
		if (get_block_head(b, s, loop))
			return (1);
	}
	ptr = b->tail;
	while (loop->input[loop->i])
	{
		new = (t_block *) malloc (sizeof(t_block));
		ptr->next = new;
		if (!new)
			return (errmsg_errno(), 1);
		if (!tokenize_input(new, s, loop))
			return (1);
		ptr = ptr->next;
	}
	ptr->next = NULL;
	b->tail = ptr;
	return (0);
}

t_block	*process_input(t_shell *s, char *input)
{
	t_loop		loop;
	t_block_ptr	buffer;
	t_block		*ptr;

	buffer = (t_block_ptr){0, 0};
	loop = (t_loop){0, 0, 0, input};
	if (get_block(&buffer, s, &loop))
		return (free_blocks(buffer.head), NULL);
	ptr = buffer.head;
	while (loop.sig)
	{
		loop = (t_loop){0, 0, loop.sig, get_input(">> ")};
		if (!loop.input)
			return (free_blocks(buffer.head), NULL);
		if (get_block(&buffer, s, &loop))
			return (free_blocks(buffer.head), NULL);
		free(loop.input);
	}
	return (buffer.head);
}

/*
	int		iter;
	char	check;
	t_block	*head;
	t_block	*temp;
	t_block	*new;

	iter = 0;
	check = 0;
	head = (t_block *) malloc (sizeof(t_block));
	if (!head)
		return (NULL);
	head->tokens = split_tokens(s, input, &check, &iter);
	if (!head->tokens)
		return (free(head), NULL);
	temp = head;
	while (input[iter] && !check)
	{
		new = (t_block *) malloc (sizeof(t_block));
		temp->next = new;
		if (!new)
			return (free_blocks(head), NULL);
		if (check)
		{
			input = get_more_input(s, &check);
			if (!input)
				return (free_blocks(head), NULL);
		}
		new->tokens = split_tokens(s, input, &check, &iter);
		if (!new->tokens)
			return (free_blocks(head), NULL);
		temp = temp->next;
	}
	temp->next = NULL;
*/