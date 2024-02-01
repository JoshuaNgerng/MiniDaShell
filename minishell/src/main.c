/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 09:42:21 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/01 09:52:44 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_ctrl_c;

static int	get_size(const t_token *t)
{
	int	out;

	out = 0;
	while (t)
	{
		out += ft_strlen(t->token);
		if (t->type)
			out ++;
		t = t->next;
	}
	return (out);
}

static char	*join_buffer(t_shell *s, t_token *t, int *len)
{
	int		i;
	char	*out;
	t_token	*ptr;

	*len = get_size(t);
	out = (char *) malloc ((*len + 1) * sizeof(char));
	if (!out)
		return (free_tokens(t), handle_error(s, 137), errmsg_errno(14), NULL);
	i = 0;
	ptr = t;
	while (ptr)
	{
		i = int_strcpy(out, i, ptr->token);
		if (ptr->type)
			out[i ++] = '\n';
		ptr = ptr->next;
	}
	out[i] = '\0';
	return (free_tokens(t), out);
}

static void	get_user_input_helper(t_shell *s, int c, char *r)
{
	if (c < 0)
		s->check = 1;
	if (r)
	{
		s->input_len = ft_strlen(r);
		add_history(r);
	}
	if (g_ctrl_c)
	{
		s->status = 1;
		g_ctrl_c = 0;
	}
}

static char	*get_user_input(t_shell *s)
{
	int		c;
	char	*r;
	t_token	*head;

	head = NULL;
	r = get_input(s, s->root.prompt);
	c = check_input(r, 0);
	if (c > 0 && c != '\'' && c != '"' && c & FILES)
	{
		c = -1;
		errmsg_var(1, "newline", 7);
	}
	if (c > 0)
	{
		if (complete_input(s, &head, r, c))
			return (free_tokens(head), NULL);
	}
	if (head)
		r = join_buffer(s, head, &s->input_len);
	return (get_user_input_helper(s, c, r), r);
}

int	main(int ac, char **av, char **env)
{
	static t_shell	s;

	(void) ac;
	errno = 0;
	if (shell_init(&s, av, env))
		return (s.status);
	g_ctrl_c = 0;
	if (signal(SIGINT, handle_signal) == SIG_ERR && \
		signal(SIGQUIT, handle_signal) == SIG_ERR)
		return (errmsg_errno(13), 1);
	s.input = get_user_input(&s);
	while (s.input)
	{
		printf("testing %d\n", s.check);
		if (!s.check)
			bash(&s);
		free_reset(&s);
		errno = 0;
		s.input = get_user_input(&s);
	}
	write(1, "exit\n", 5);
	return (free_all(&s), s.status);
}
