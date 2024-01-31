/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 09:42:21 by jngerng           #+#    #+#             */
/*   Updated: 2024/01/31 11:12:31 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	int_strcpy(char *dst, int index, const char *src)
// {
// 	int	j;

// 	j = -1;
// 	while (src[++ j])
// 		dst[index ++] = src[j];
// 	return (index);
// }

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
	if (c > 0 && c != '\'' && c != '"' && c & FILES)
	{
		c = -1;
		s->check = 1;
		errmsg_var(1, "newline", 7);
	}
	if (c > 0)
	{
		if (complete_input(s, &head, r, c))
			return (free_tokens(head), NULL);
	}
	if (head)
	{
		r = join_buffer(s, head, &s->input_len);
		if (!r)
			handle_error(s, 137);
	}
	if (c < 0)
		s->check = 1;
	if (r)
	{
		s->input_len = ft_strlen(r);
		add_history(r);
	}
	// printf("test added to history %s\n", r);
	return (r);
}

int	main(int ac, char **av, char **env)
{
	static t_shell	s;

	(void) ac;
	(void) av;
	errno = 0;
	if (shell_init(&s, env))
		return (s.status);
	if (signal(SIGINT, handle_signal) == SIG_ERR && signal(SIGQUIT, handle_signal) == SIG_ERR)
	{
		perror("Error! Signal handler!\n"); // errmsg
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
	return (free_all(&s), s.status);
}
