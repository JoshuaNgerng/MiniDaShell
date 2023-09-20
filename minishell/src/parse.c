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

int	get_size(int size[4], t_tokens *t, int *sig)
{
	int	iter;

	iter = 0;
	ft_bzero(size, 4 * sizeof(int));
	while (t)
	{
		iter ++;
		if (t->type == 'c')
			size[0] ++;
		if (t->type == 'r')
			size[1] ++;
		if (t->type == 'h')
			size[2] ++;
		if (t->type == 'w')
			size[3] ++;
		if (t->type == 'a')
			size[3] ++;
		if (t->type == 'p')
			return (iter);
		if (t->type == 'n' || t->type == 'o')
		{
			*sig = 1;
			return (iter);
		}
		t = t->next;
	}
	*sig = 1;
	return (iter);
}

t_data	*malloc_data_node(int size[5])
{
	t_data	*out;

	out = (t_data *) malloc (sizeof(t_data));
	if (!out)
		return (NULL);
	out->cmd = (char **) malloc ((size[0] + 1) * sizeof(char *));
	if (!out->cmd)
		return (free(out), NULL);
	out->f_read = (char **) malloc ((size[1] + 1) * sizeof(char *));
	if (!out->cmd)
		return (free(out), free(out->cmd), NULL);
	out->here_doc = (char **) malloc ((size[2] + 1) * sizeof(char *));
	if (!out->here_doc)
		return (free(out), free(out->cmd), free(out->f_read), NULL);
	out->f_out = (t_file *) malloc ((size[3] + 1) * sizeof(t_file));
	if (!out->f_out)
		return (free(out), free(out->cmd), free(out->f_read), \
				free(out->here_doc), NULL);
	return (out);
}

/*
rewrite to get proper in out on data struct
*/
t_tokens	*data_init(t_data *data, int lim, t_tokens *t)
{
	int	index[4];

	ft_bzero(index, 4 * sizeof(int));
	while (lim -- > 0)
	{
		if (t->type == 'c')
			data->cmd[index[0] ++] = t->token;
		if (t->type == 'r')
		{
			data->f_read[index[1] ++] = t->token;
			data->in = 'r';
		}
		if (t->type == 'h')
		{
			data->here_doc[index[2] ++] = t->token;
			data->in = 'h';
		}
		if (t->type == 'w')
		{
			data->f_out[index[3]].f_name = t->token;
			data->f_out[index[3] ++].f_type = 'w';
			data->out = 'w';
		}
		if (t->type == 'a')
		{
			data->f_out[index[3]].f_name = t->token;
			data->f_out[index[3] ++].f_type = 'a';
			data->out = 'a';
		}
		t = t->next;
	}
	data->cmd[index[0]] = NULL;
	data->f_read[index[1]] = NULL;
	data->here_doc[index[2]] = NULL;
	data->f_out[index[3]].f_name = NULL;
	data->f_out[index[3]].f_type = '\0';
	return (t);
}

t_data	*get_data_node(t_tokens **start, int *sig)
{
	int			iter;
	int			size[5];
	t_tokens	*t;
	t_data		*out;

	// printf("testing node\n");
	iter = get_size(size, *start, sig);
	out = malloc_data_node(size);
	if (!out)
		return (sp_errmsg(0, "data_node (malloc)"), NULL);
	out->out = '\0';
	out->in = '\0';
	t = data_init(out, iter, *start);
	*start = t;
	return (out);
}

t_tokens	*loop_data(t_proc *in, t_tokens *t)
{
	int		sig;
	t_data	*buffer;
	t_data	*new;

	sig = 0;
	in->data = get_data_node(&t, &sig);
	if (!in->data)
		return (NULL);
	buffer = in->data;
	while (!sig)
	{
		new = get_data_node(&t, &sig);
		buffer->next = new;
		if (!new)
			return (free_data(in->data), NULL);
		buffer = buffer->next;
		in->num ++;
		if (new->out == 'a')
			in->add ++;
		if (!t)
			break ;
		if (t->type == 'p')
			t = t->next;
	}
	buffer->next = NULL;
	// dev_print_data(in->data);
	return (t);
}

t_proc	*get_process_node(t_tokens **start)
{
	t_proc	*out;

	out = (t_proc *) malloc (sizeof(t_proc));
	if (!out)
		return (NULL);
	out->num = 1;
	out->add = 0;
	out->type = '\0';
	*start = loop_data(out, *start);
	if (errno)
		return (free(out), NULL);
	out->pid = (int *) malloc (out->num * sizeof(int));
	if (!out->pid)
		return (free(out), free_data(out->data), NULL);
	out->lim = out->num + out->add - 1;
	if (!out->lim)
		out->pfd = NULL;
	else
	{
		out->pfd = (int *) malloc (out->lim * 2 * sizeof(int));
		if (!out->pfd)
			return (free(out), free_data(out->data), free(out->pid), NULL);
	}
	if (*start)
		out->type = start[0]->type;
	return (out);
}

t_proc	*process_init(t_tokens *start)
{
	t_proc		*out;
	t_proc		*buffer;
	t_proc		*new;
	t_tokens	*t;

	t = start;
	out = get_process_node(&t);
	if (!out)
		return (NULL);
	buffer = out;
	// printf("testing loop before iter\n");
	while (t)
	{
		new = get_process_node(&t);
		buffer->next = new;
		// printf("testing loop iter\n");
		if (!new)
			return (free_proc(out), sp_errmsg(0, "get_process_node (malloc): "), NULL);
		buffer = buffer->next;
		// printf("test loop address %p\n", t);
		// if (t)
		// 	printf("test loop value %s\n", t->token);
		// if (t)
		// {
		// 	if (!t->token)
		// 	{
		// 		printf("test loop value %s\n", t->token);
		// 		t = t->next;
		// 	}
		// }
	}
	buffer->next = NULL;
	return (out);
}

int	parse_info(char *input, t_shell *s)
{
	t_tokens	*t;
	t_tokens	*f;

	input = do_expansion(input);
	if (!input)
		return (sp_errmsg(0, "expansion: "), 1);
	t = ft_split_tokens(input);
	if (!t)
		return (1);
	// dev_print_tokens(t);
	s->process = process_init(t);
	if (!s->process)
		return (free_tokens(t), 1);
	while (t)
	{
		f = t;
		t = t->next;
		free(f);
	}
	return (0);
}
