/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:31:16 by jngerng           #+#    #+#             */
/*   Updated: 2023/12/04 22:12:04 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	int_strcpy(char *dst, int index, const char *src)
{
	int	j;

	j = -1;
	while (src[++ j])
		dst[index ++] = src[j];
	return (index);
}

int	get_size(t_token *t)
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
		i = int_strcpy(out, i, ptr->token);
		if (ptr->type)
			out[i ++] = '\n';
		ptr = ptr->next;
	}
	out[i] = '\0';
	return (free_tokens(t), out);
}

char	*get_user_input(t_shell *s)
{
	int		c;
	char	*r;
	t_token	*head;

	head = NULL;
	r = get_input(s, s->root.prompt);
	c = check_input(r, 0);
	if (c > 0 && c & FILES)
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
	{
		r = join_buffer(s, head);
		if (!r)
			handle_error(s, 137);
	}
	if (r)
		add_history(r);
	// printf("test added to history %s\n", r);
	if (c == -1)
		s->check = 1;
	return (r);
}

int	main(int ac, char **av, char **env)
{
	static t_shell	s;

	(void) ac;
	(void) av;
	errno = 0;
	if (shell_init(&s, env))
		return (s.ext_code);
	if (signal(SIGINT, handle_signal) == SIG_ERR && signal(SIGQUIT, handle_signal) == SIG_ERR)
	{
		perror("Error! Signal handler!\n");
		return (1);
	}
	s.input = get_user_input(&s);
	while (s.input)
	{
		if (!s.check)
			bash(&s);
		free_reset(&s);
		errno = 0;
		// system("leaks minishell");
		s.input = get_user_input(&s);
	}
	write(1, "exit\n", 5);
	// system("leaks minishell");
	return (free_all(&s), s.ext_code);
}
