/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:40:53 by mukhairu          #+#    #+#             */
/*   Updated: 2023/09/20 19:00:49 by mukhairu         ###   ########.fr       */
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
		printf("Stuff happends here: Change directory. Update must be made\n");
	return (0);
}

// int	main(void)
// {
// 	char	*freer;
// 	// signal(SIGQUIT, SIG_IGN);
// 	printf("Hello, welcome to MINIDASHELL!\n");
// 	if (signal(SIGINT, handle_signal) == SIG_ERR
// 		&& signal(SIGQUIT, handle_signal) == SIG_ERR)
// 	{
// 		perror("Error! Signal handler!\n");
// 		return (1);
// 	}
// 	freer = readline("MiniDaShell %");
// 	while (freer && (freer, "exit", 5))
// 	{
// 		free(freer);
// 		freer = readline("MiniDaShell %");
// 	}
// 	if (!freer)
// 		free(freer);
// 	printf("exit\n");
// 	return (0);
// }

int main(void)
{
	char *freer;
	// signal(SIGQUIT, SIG_IGN);
	printf("Hello, welcome to MINIDASHELL!\n");
	if (signal(SIGINT, handle_signal) == SIG_ERR && signal(SIGQUIT, handle_signal) == SIG_ERR)
	{
		perror("Error! Signal handler!\n");
		return (1);
	}
	while (1)
	{
		freer = readline("MiniDaShell %");
		if (builtin_runs(freer))
			break ;
		free(freer);
	}
	if (freer)
		free(freer);
	printf("exit\n");
	return (0);
}
