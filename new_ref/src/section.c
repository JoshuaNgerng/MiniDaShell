/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:56:23 by jngerng           #+#    #+#             */
/*   Updated: 2023/12/04 20:10:17 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cont_section_list(t_sect *new, t_ptr_s *ptr)
{
	if (!ptr->head)
	{
		ptr->head = new;
		ptr->tail = ptr->head;
	}
	else
	{
		ptr->tail->next = new;
		ptr->tail = ptr->tail->next;
	}
	ptr->tail->next = NULL;
}

int	add_section(t_shell *s, t_ptr_s	*ptr, int *index)
{
	int		type;
	t_sect	*new;
	t_ptr_p	buffer;

	buffer = (t_ptr_p){0, 0};
	new = (t_sect *) malloc(sizeof(t_sect));
	if (!new)
		return (1);
	new->pid = 0;
	type = 0;
	while (s->input[*index] && !(type & LOGIC))
	{
		type = add_process(s, &buffer, new, index);
		if (type < 0)
			return (1);
	}
	new->operator = type;
	new->block = buffer.head;
	cont_section_list(new, ptr);
	return (0);
}

int	tokenize_and_sectioning(t_shell *s, t_processor	*p)
{
	int		index;
	t_ptr_s	buffer;

	index = 0;
	buffer = (t_ptr_s){0, 0};
	while (s->input[index])
	{
		if (add_section(s, &buffer, &index))
			return (free_sect_list(buffer.head), 1);
	}
	p->buffer = buffer.head;
	return (0);
}
