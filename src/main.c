/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:40:53 by mukhairu          #+#    #+#             */
/*   Updated: 2023/09/21 19:06:49 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// int	exit_check(char *text)
// {
// 	if (!text)
// 		return (0);
// 	if (!ft_strncmp(text, "exit", 5))
// 	{
// 		return (0);
// 	}
// 	return (1);
// }

void go_cwd(char *input)
{
	int i;

	i = 0;
	while (input[i] != ' ' && input[i])
		i++;
	while (input[i] == ' ' && input[i])
		i++;
	if (chdir(&input[i]))
		perror(&input[i]);
}

//reuturn 0 means success, 1 means failed
int	builtin_runs(char *usr_int)
{
	char	cwd[256];

	if (!usr_int)
		return (1);
	if (!ft_strncmp(usr_int, "exit", 5))
		return (1);
	if (usr_int && *usr_int)
		add_history(usr_int);
	if (!ft_strncmp(usr_int, "pwd", 4))
	{
		getcwd(cwd, sizeof(cwd));
		printf("current directory: %s\n", cwd);
	}
	if (!ft_strncmp(usr_int, "cd", 2))
		go_cwd(usr_int);
	return (0);
}

char	*get_prompt(void)
{
	char	root[] = "MiniDaShell:";
	char	dir[256];
	char	*out;
	char	*temo;

	getcwd(dir, sizeof(dir));
	out = ft_strjoin(root, dir);
	if (!out)
		return (NULL);
	temo = out;
	out = ft_strjoin(out, "% ");
	if (!out)
		return (free(temo), NULL);
	free(temo);
	return(out);
}

int main(void)
{
	char	*prompt;
	char	*freer;
	// signal(SIGQUIT, SIG_IGN);
	printf("Hello, welcome to MINIDASHELL!\n");
	if (signal(SIGINT, handle_signal) == SIG_ERR && signal(SIGQUIT, handle_signal) == SIG_ERR)
	{
		perror("Error! Signal handler!\n");
		return (1);
	}
	while (1)
	{
		prompt = get_prompt();
		freer = readline(prompt);
		if (builtin_runs(freer))
			break ;
		free(freer);
		free(prompt);
	}
	if (freer)
		free(freer);
	if (prompt)
		free(prompt);
	printf("exit\n");
	return (0);
}
