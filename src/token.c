/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:07:38 by jngerng           #+#    #+#             */
/*   Updated: 2023/08/19 13:07:38 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
check sp characthers
can add a second para if needed
flag special characthers > <
block together open quotations
ending characthers are \0 | (add more later if discovered) (for later)
priority is get quo first
then <>
then other characther
the type will determine on context 
ex 
each partition represent a cmd to fork and exe 
with the clue where to redirect output and input too
new partition for now assume it is pipe from before (no && for now and try || later)
if there is quotation it is huge block
if quotation is surronding < or > it is treated as text and not redirection
if there is a < or > behind a block of text then its a file
if there is | (later & and other symbols) it treated as a new partition
*/

int	token_init(t_tokens *t, char *input, int i)
{
	int	begin;

	begin = i;
	if (input[i] == '\"')
	{
		i ++;
		begin = i;
		while (input[i] && !(input[i] == '\"' && input[i - 1] != '\\'))
			i ++;
		t->token = ft_substr(input, begin, i - begin);
		i ++;
	}
	else if (input[i] == '\'')
	{
		i ++;
		begin = i;
		while (input[i] && input[i] != '\'')
			i ++;
		t->token = ft_substr(input, begin, i - begin);
		i ++;
	}
	else
	{
		while (input[i] && !ft_checkset(input[i], " |<>"))
			i ++;
		t->token = ft_substr(input, begin, i - begin);
	}
	return (i);
}

char	check_type(char *input, int *index)
{
	int		i;
	char	out;

	i = *index;
	out = 0;
	if (input[i] == '|' && input[i + 1] == '|')
		out = 'o';
	else if (input[i] == '>' && input[i + 1] == '>')
		out = 'a';
	else if (input[i] == '<' && input[i + 1] == '<')
		out = 'h';
	else if (input[i] == '<' && input[i + 1] == '>')
		out = 'b';
	else if (input[i] == '|')
		out = 'p';
	else if (input[i] == '>')
		out = 'w';
	else if (input[i] == '<')
		out = 'r';
	if (out == 'r' || out == 'w' || out == 'p')
		*index = i + 1;
	else if (out == 'a' || out == 'h' || out == 'b' || out == 'o')
		*index = i + 2;
	return (out);
}

int	get_token(t_tokens *t, char *input, int start, int *num)
{
	int	i;

	i = start;
	t->type = 'c';
	while (ft_checkset(input[i], " "))
		i ++;
	if (ft_checkset(input[i], "<>|"))
		t->type = check_type(input, &i);
	if (t->type == 'p' || t->type == 'o')
	{
		t->token = NULL;
		(*num) ++;
		return (i);
	}
	while (ft_checkset(input[i], " "))
		i ++;
	if (input[i] && !ft_checkset(input[i], "<>|"))
		i = token_init(t, input, i);
	else if (!input[i])
	{
		t->token = NULL;
		t->type = 0;
	}
	return (i);
}

t_tokens	*ft_split_tokens(char *input, int *num)
{
	int			i;
	t_tokens	*head;
	t_tokens	*temp;
	t_tokens	*new;

	i = 0;
	errno = 0;
	*num = 1;
	head = (t_tokens *) malloc (sizeof(t_tokens));
	if (!head)
		return (NULL);
	i = get_token(head, input, i, num);
	temp = head;
	while (input[i])
	{
		new = (t_tokens *) malloc (sizeof(t_tokens));
		if (!new)
			return (free_tokens(head), NULL);
		i = get_token(new, input, i, num);
		if (errno)
			return (free_tokens(head), NULL);
		temp->next = new;
		temp = temp->next;
	}
	temp->next = NULL;
	return (head);
}
