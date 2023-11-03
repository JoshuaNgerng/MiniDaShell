/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:49:54 by mukhairu          #+#    #+#             */
/*   Updated: 2023/11/03 17:23:07 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

//LinkedList for the env
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

//Colour Text
# define RED "\033[0;31m"
# define GREEN "\033[0; 32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"

//env
t_env	*ft_env_new(char *key, char *value);
void	ft_env_add(t_env **list, t_env *new);
void	ft_env_addback(t_env **list, t_env *new);
t_env	*get_env_state(char **env);
void	free_env_1(t_env *list);
void	free_all_env(t_env *list);
void	print_env(t_env *env);

void	free2d(char **str);

#endif // !MINISHELL_H
