/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 04:53:00 by jngerng           #+#    #+#             */
/*   Updated: 2023/08/18 04:53:00 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
user interface can add more stuff later
*/
char	*get_input(char *prompt)
{
	char	*r;

	r = readline(prompt);
	if (!r)
		return (NULL);
	while (!r[0])
		r = readline(prompt);
	if (r && r[0])
		add_history(r);
	return (r);
}

static char	*help_path(char **env)
{
	char	**buffer;

	buffer = env;
	while (buffer)
	{
		if (!ft_strncmp(*buffer, "PATH", 4))
			break ;
		buffer ++;
	}
	return (*(buffer) + 5);
}

static char	**get_paths(char **env)
{
	char	**paths;
	char	**buffer;
	char	*temp;

	paths = ft_split(help_path(env), ':');
	if (!paths)
		return (NULL);
	buffer = paths;
	while (*buffer)
	{
		temp = *buffer;
		*buffer = ft_strjoin(*buffer, "/");
		if (!(*buffer))
			return (free_strs(paths), free(temp), NULL);
		free(temp);
		buffer ++;
	}
	return (paths);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	*input;
	t_shell	shell;

	shell = (t_shell){0, env, get_paths(env), 0};
	if (!shell.path)
		return (sp_errmsg(0,"get_paths (malloc): "), 1);
	input = get_input("test input: ");
	if (!input)
		return (free_all(&shell), sp_errmsg(1, NULL), 1);
	while (ft_strncmp(&input[0], "exit", 5))
	{
		if (parse_info(input, &shell))
			return (free(input), free_all(&shell), sp_errmsg(2, NULL), 1);
		free(input);
		dev_print_proc(shell.process);
		if (do_bash(&shell))
			return (free_all(&shell), 1);
		free_proc(shell.process);
		shell.process = NULL;
		input = get_input("test input: ");
		if (!input)
			return (free_all(&shell), sp_errmsg(1, NULL), 1);
	}
	return (free(input), free_all(&shell), 0);
}
