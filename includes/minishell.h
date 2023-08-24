/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 02:11:13 by jngerng           #+#    #+#             */
/*   Updated: 2023/08/18 02:11:13 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include "libft.h"

typedef struct s_tokens
{
	char			*token;
	char			type;
	struct s_tokens	*next;
}	t_tokens;

/*
every partion have one cmd
only one active input file nearest to a cmd (however it still detects other input file)
create all output file but only further file is writen into
*/

// typedef struct s_file
// {
// 	char	*filename;
// 	char	file_type;
// }	t_file;

typedef struct s_data
{
	char	**cmd;
	char	**file_read;
	char	**here_doc;
	char	**file_write;
	char	**file_append;
}	t_data;

typedef	struct s_shell
{
	int		num;
	t_data	*data;
	int		*pid;
	int		*pfd;
}	t_shell;

void		free_all(t_shell *s);
void		free_strs(char **s);
void		free_node(t_data *in);
void		free_tokens(t_tokens *t);
int			ft_checkset(char const s, char const *set);
void		*sp_errmsg(int	e, char *msg, int err);
int			parse_info(char *input, t_shell *s);
t_tokens	*ft_split_tokens(char *input, int *num);
void		do_bash(t_shell *s);
void		wait_bash(t_shell *s);

void	print_info(t_shell s);
void	dev_print_tokens(t_tokens *t);

#endif