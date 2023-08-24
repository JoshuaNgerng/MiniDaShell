/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:14:31 by jngerng           #+#    #+#             */
/*   Updated: 2023/08/18 18:14:31 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
do expansion 
check file (before after <>)
check cmd ()
in cmd , check options,
*/

char	*do_expansion(char *input)
{
	(void)input;
	return (input);
}

void	get_size(t_tokens *t, int size[5])
{
	ft_bzero(size, 5 * sizeof(int));
	while (t)
	{
		if (t->type == 'o' || t->type == 'p')
			return ;
		if (t->type == 'c')
			size[0]++;
		if (t->type == 'r')
			size[1]++;
		if (t->type == 'h')
			size[2]++;
		if (t->type == 'w')
			size[3]++;
		if (t->type == 'a')
			size[4]++;
		t = t->next;
	}
}

t_tokens	*loop_tokens(t_shell *shell, int i, t_tokens *in)
{
	int			*index;
	t_tokens	*t;

	index = (int[5]){0, 0, 0, 0, 0};
	t = in;
	while (t && t->type != 'p' && t->type != 'o')
	{
		if (t->type == 'c')
			shell->data[i].cmd[index[0]++] = t->token;
		else if (t->type == 'r')
			shell->data[i].file_read[index[1]++] = t->token;
		else if (t->type == 'h')
			shell->data[i].here_doc[index[2]++] = t->token;
		else if (t->type == 'w')
			shell->data[i].file_write[index[3]++] = t->token;
		else if (t->type == 'a')
			shell->data[i].file_append[index[4]++] = t->token;
		t = t->next;
	}
	shell->data[i].cmd[index[0]] = NULL;
	shell->data[i].file_read[index[1]] = NULL;
	shell->data[i].here_doc[index[2]] = NULL;
	shell->data[i].file_write[index[3]] = NULL;
	shell->data[i].file_append[index[4]] = NULL;
	return (t);
}

int	data_init(t_shell *shell, t_tokens *t)
{
	int			i;
	int			size[5];
	t_tokens	*buffer;

	i = -1;
	errno = 0;
	buffer = t;
	while (++ i < shell->num)
	{
		get_size(buffer, size);
		shell->data[i].cmd = (char **) malloc ((size[0] + 1) * sizeof(char *));
		shell->data[i].file_read = (char **) malloc ((size[1] + 1) * sizeof(char *));
		shell->data[i].here_doc = (char **) malloc ((size[2] + 1) * sizeof(char *));
		shell->data[i].file_write = (char **) malloc ((size[3] + 1) * sizeof(char *));
		shell->data[i].file_append = (char **) malloc ((size[4] + 1) * sizeof(char *));
		if (errno)
			return (1);
		buffer = loop_tokens(shell, i, buffer);
		if (buffer)
			if (buffer->type == 'p' || buffer->type == 'o')
				buffer = buffer->next;
	}
	return (0);
}

int	parse_info(char *input, t_shell *s)
{
	t_tokens	*t;
	t_tokens	*f;
	int			num;

	num = 1;
	input = do_expansion(input);
	t = ft_split_tokens(input, &num);
	if (!t)
		return (1);
	dev_print_tokens(t);
	s->num = num;
	s->data = (t_data *) malloc (s->num * sizeof(t_data));
	s->pfd = (int *) malloc (s->num * sizeof(int));
	s->pid = (int *) malloc (s->num * sizeof(int));
	if (!s->data || !s->pfd || !s->pid)
		return (free_all(s), free_tokens(t), 1);
	if (data_init(s, t))
		return (free_all(s), free_tokens(t), 1);
	//dev_print_tokens(t);
	while (t)
	{
		f = t;
		t = t->next;
		printf("test free token %s type %c\n", f->token, f->type);
		free(f);
	}
	return (0);
}