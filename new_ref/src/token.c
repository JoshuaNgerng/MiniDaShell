/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:11:00 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/10 08:49:44 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	check_logical_operator(t_loop *loop)
{
	int		i;
	char	out;

	i = loop->iter;
	out = 0;
	if (loop->input[i] == '|' && loop->input[i + 1] == '|')
		out = 'o';
	else if (loop->input[i] == '&' && loop->input[i + 1] == '&')
		out = 'n';
	else if (loop->input[i] == '|')
		out = 'p';
	else if (loop->input[i] == '&' && loop->input[i + 1] != '&')
		errmsg_var(1, "&");
	loop->iter = i + 1;
	if (out == 'o' || out == 'n')
		loop->iter ++;
	return (out);
}

char	check_redirect(t_loop *loop)
{
	int		i;
	char	out;

	i = loop->iter;
	out = 0;
	if (loop->input[i] == '>' && loop->input[i + 1] == '>')
		out = 'a';
	else if (loop->input[i] == '<' && loop->input[i + 1] == '<')
		out = 'h';
	else if (loop->input[i] == '<' && loop->input[i + 1] == '>')
		out = 's';
	else if (loop->input[i] == '>' && loop->input[i + 1] == '<')
		return (out);
	else if (loop->input[i] == '>')
		out = 'w';
	else if (loop->input[i] == '<')
		out = 'r';
	loop->iter = i + 1;
	else if (out == 'a' || out == 'h')
		loop->iter ++;
	return (out);
}

int	get_index_token(t_loop *loop)
{
	int	i;

	i = loop->iter;
	loop->begin = loop->iter;
	while (loop->input[i] && loop->input[i] != ' ')
	{
		if (!ft_isascii(loop->input[i]))
			return (errmsg(1), 1);
		if (loop->input[i] == '"' || loop->input[i] == '\'')
		{
			loop->sig = loop->input[i];
			while (loop->input[i] && loop->input[i] != loop->sig)
				i ++;
			if (input[i] == loop->sig)
				loop->sig = 0;
		}
		if (ft_checkset(loop->input[i], "&|<>()"))
			break ;
		i ++;
	}
	loop->iter = i;
	return (0);
}

int	find_intial_token(t_token *t, t_loop *loop)
{
	loop->iter = pass_space(loop->input, 0);
	if (ft_checkset(loop->input[loop->iter], "&|"))
		return (1);
	if (input[loop->iter] == '>' && input[loop->iter + 1] == '<')
		return (errmsg_var(1, '<', 1), 1);
	if (input[loop->iter] == '(')
	{
		t->type = s;
		loop->begin = loop->iter;
		loop->iter ++;
		return (0);
	}
	if (ft_checkset(loop->input[loop->iter], "<>"))
		t->type = check_redirect(loop);
	loop->iter = pass_space(loop->input, loop->iter);
	return (get_index_token(loop));
}

int	find_token(t_token *t, t_loop *loop)
{
	t->type = c;
	if (!loop->iter)
		return (find_intial_token(t, loop));
	loop->iter = pass_space(loop->input, loop->iter);
	if ()
		;
	else if ()
		;
	else if ()
		;
	loop->iter = pass_space(loop->input, loop->iter);
	return (0);
}

int	head_init(t_block *b, t_shell *s, t_loop *loop)
{
	int	j;

	b->logic = 0;
	b->brackets = 0;
	b->tokens = (t_token *) malloc (sizeof(t_token));
	if (!(b->tokens))
		return (handle_error(s, 137), 1);
	if (find_token(b->tokens, loop))
		return (handle_error(s, 2), 1);
	b->tokens->token = ft_substr(loop->input, loop->begin, \
									loop->iter - loop->begin);
	if (!b->tokens->token)
		return (free(b->tokens), handle_error(s, 137), 1);
	b->tokens->next = NULL;
	return (0);
}

int	tokenize_input(t_block *b, t_shell *s, t_loop *loop)
{
	t_token	*ptr;
	t_token	*new;

	if (head_init(b, s, loop))
		return (1);
	ptr = b->tokens;
	while (loop->input[loop->iter])
	{
		if (loop->input[loop->iter] == '&' || loop->input[loop->iter] == '|')
		{
			b->logic = check_logical_operator(loop);
			if (!b->logic)
				return (1);
			// if (b->logic != 'p')
			// break ;
		}
		new = (t_token *) malloc (sizeof(t_token));
		ptr->next = new;
		if (!new)
			return (1);
		if (token_init(new, loop))
			return (1);
		ptr = ptr->next;
	}
	ptr->next = NULL;
	return (0);
}

/*
	int		i;
	int		j;
	t_token	*head;
	t_token	*temp;
	t_token	*new;

	if (head_init(&head, input))
		return (NULL);
	temp = head;
	while (input[j])
	{
		i = j;
		j = find_token_in_input(s, input, i);
		if (j < 0)
			return (free_tokens(head), NULL);
	}
	temp->next = NULL;
	return (head);
*/