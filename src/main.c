/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:40:53 by mukhairu          #+#    #+#             */
/*   Updated: 2023/11/12 17:22:11 by mukhairu         ###   ########.fr       */
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

char	*get_prompt(char *root)
{
	char	dir[256];
	char	*out;
	char	*temo;

	// printf(GREEN);
	getcwd(dir, sizeof(dir));
	out = ft_strjoin(root, dir);
	if (!out)
		return (NULL);
	// printf(RESET);
	temo = out;
	printf(YELLOW);
	out = ft_strjoin(out, "\033[0m % ");
	if (!out)
		return (free(temo), NULL);
	free(temo);
	return(out);
}

char	*get_env_ptr(char **env, char *var, int len)
{;
	int		i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], var, len))
			return (env[i] + len + 1);
	}
	return (NULL);
}

char	*root_init(char **env)
{
	char	*name1;
	char	*name2;
	char	*temp;
	char	*out;

	name2 = get_env_ptr(env, "NAME", 4);
	if (!name2)
		name2 = get_env_ptr(env, "LOGNAME", 7);
	name1 = get_env_ptr(env, "LOGNAME", 7);
	out = ft_strjoin(name1, "@");
	temp = out;
	printf("AAAAA: %s\n", name2);
	out = ft_strjoin(out, name2);
	free(temp);
	temp = out;
	out = ft_strjoin(out, ":\033[0;34m");
	free(temp);
	return (out);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	*root;
	char	*prompt;
	char	*freer;
	t_env	*env_state;

	env_state = get_env_state(env);
	print_env(env_state);
	root = root_init(env);
	// signal(SIGQUIT, SIG_IGN);
	printf("Hello, welcome to MINIDASHELL!\n");
	if (signal(SIGINT, handle_signal) == SIG_ERR && signal(SIGQUIT, handle_signal) == SIG_ERR)
	{
		perror("Error! Signal handler!\n");
		return (1);
	}
	while (1)
	{
		prompt = get_prompt(root);
		
		freer = readline(prompt);
		
		if (builtin_runs(freer))
			break ;
		export(env_state, "limau=ctrl");
		unset(env_state, "check for limau any errors");
		free(freer);
		free(prompt);
	}
	if (freer)
		free(freer);
	if (prompt)
		free(prompt);
	free(root);
	print_env(env_state);
	free_all_env(env_state);
	printf("exit\n");
	return (0);
}
