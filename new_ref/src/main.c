/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:31:16 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/17 16:28:05 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_size(t_token *t)
{
	int	out;

	out = 0;
	while (t)
	{
		out += ft_strlen(t->token);
		if (!t->type)
			out ++;
		t = t->next;
	}
	return (out);
}

char	*join_buffer(t_shell *s, t_token *t)
{
	int		i;
	int		l;
	char	*out;
	t_token	*ptr;

	l = get_size(t);
	out = (char *) malloc ((l + 1) * sizeof(char));
	if (!out)
		return (free_tokens(t), handle_error(s, 137), NULL);
	i = 0;
	ptr = t;
	while (ptr)
	{
		i = int_strcpy(out, i, t->token);
		if (!t->type)
			out[i ++] = '\n';
		ptr = ptr->next;
	}
	out[i] = '\0';
	return (free_tokens(t), out);
}

char	*get_user_input(t_shell *s)
{
	char	c;
	char	*r;
	t_token	*head;

	head = NULL;
	r = get_input(s, s->root.prompt);
	c = check_input(r, 0);
	if (ft_checkset(c, "hrwa"))
	{
		c = -1;
		errmsg_var();
	}
	if (c > 0 && c != 'c')
	{
		if (complete_input(s, &head, r, c))
			return (free_tokens(head), NULL);
	}
	if (head)
	{
		r = join_buffer(s, head);
		if (!r)
			handle_error(s, 137);
	}
	if (r)
		add_history(r);
	if (c == -1)
		s->input = 1;
	return (r);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)env;
	char	*input;
	t_shell	s;

	if (shell_init(&s))
		return (s.ext_code);
	input = get_input(s.root);
	while (input)
	{
		errno = 0;
		if (!s.input)
		{
			bash();
		}
		s.input = 0;
		free(input);
		input = get_input(s.root);
	}
	return (free_all(&s), s.ext_code);
}
