/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:31:16 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/12 02:14:46 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_size(t_token *t)
{
	int	out;


	return (out);
}

char	*join_buffer(t_shell *s, t_token *t)
{
	char	*out;
	int		i;
	int		l;

	l = get_size();
	out = (char *) malloc ((l + 1) * sizeof(char));
	if (!out)
		return (free_tokens(t), handle_error(s, 137), NULL);
	i = -1;
	while (++ i < l)
	{
		out[i] = ;
	}
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
	if (c > 0)
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
		return (ext_code());
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
	return (free_all(&s), ext_code());
}
