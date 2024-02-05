/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errmsg_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:51:19 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/01 15:03:43 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	errmsg_ptr_1(int e)
{
	if (e == 1)
		write(2, "Cannot access enviroment variable: ", 35);
	else if (e == 2)
		write(2, "readline: ", 10);
	else if (e == 3)
		write(2, "Cannot get directory path: ", 27);
	else if (e == 4)
		write(2, "t_token (malloc): ", 18);
	else if (e == 5)
		write(2, "t_proc (malloc): ", 17);
	else if (e == 6)
		write(2, "t_buffer (malloc): ", 19);
	else if (e == 7)
		write(2, "subshell (fork): ", 17);
	else if (e == 8)
		write(2, "t_env (malloc): ", 16);
	else if (e == 9)
		write(2, "dup2: ", 6);
	else if (e == 10)
		write(2, "find_cmd (malloc): ", 19);
	else if (e == 11)
		write(2, "get_cmd_array (malloc): ", 24);
	else if (e == 12)
		write(2, "here_doc_pipe (malloc): ", 24);
}

static void	errmsg_ptr_2(int e)
{
	if (e == 13)
		write(2, "Cannot initiate signal handler: ", 32);
	else if (e == 14)
		write(2, "join_buffer[input] (malloc): ", 29);
	else if (e == 15)
		write(2, "pid and pipe (malloc): ", 23);
	else if (e == 16)
		write(2, "itoa (malloc): ", 15);
	else if (e == 17)
		write(2, "t_token[expand] (malloc): ", 26);
	else if (e == 18)
		write(2, "join_buffer_star (malloc): ", 27);
	else if (e == 19)
		write(2, "process_file; ", 14);
	else if (e == 20)
		write(2, "Cannot make pipe[expand]: ", 26);
	else if (e == 21)
		write(2, "Cannot make child process[expand]: ", 35);
	else if (e == 22)
		write(2, "tcgetattr cannot run: ", 22);
	else if (e == 23)
		write(2, "tcsetattr cannot run: ", 22);
}

void	*errmsg_errno(int e)
{
	char	*ptr;

	errmsg_name(NULL);
	if (e < 12)
		errmsg_ptr_1(e);
	else
		errmsg_ptr_2(e);
	ptr = strerror(errno);
	if (ptr)
		write(2, ptr, ft_strlen(ptr));
	write(2, "\n", 1);
	errno = 0;
	return (NULL);
}

int	errmsg_check(char *cmd, t_token **list, int quo)
{
	t_token	*ptr;

	ptr = *list;
	if (!quo)
	{
		if (ft_strchr(ptr->token, ' '))
		{
			if (cmd[0] < 0)
				cmd[0] *= -1;
			write(2, cmd, ptr->type + 1);
			return (1);
		}
	}
	ptr = ptr->next;
	*list = ptr;
	return (0);
}

void	*errmsg_expand(char *cmd, t_token *list, t_token *list_malloc)
{
	int	i;
	int	quo;

	i = -1;
	quo = 0;
	errmsg_name(NULL);
	while (cmd[++ i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
			quo = read_quo(cmd[i], quo);
		else if (cmd[i] == '$' && quo != '\'')
		{
			if (errmsg_check(&cmd[i], &list, quo))
				break ;
		}
		else if (cmd[i] < 0 && quo != '\'')
		{
			if (errmsg_check(&cmd[i], &list_malloc, quo))
				break ;
		}
	}
	write(2, ": ambigous redirect\n", 20);
	return (NULL);
}
