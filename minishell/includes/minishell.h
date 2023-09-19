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

typedef struct s_size_data
{
	int					cmd;
	int					f_read;
	int					here_doc;
	int					f_write;
	int					f_append;
	struct s_size_data	*next;
}	t_size_data;

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

typedef struct s_file
{
	char	*f_name;
	char	f_type;
}	t_file;


// change file system struct
typedef struct s_data
{
	char			**cmd;
	char			**f_read;
	char			**here_doc;
	t_file			*f_out;
	char			out;
	char			in;
	struct s_data	*next;
}	t_data;

typedef struct s_proc
{
	char			type;
	int				num;
	int				add;
	int				lim;				
	t_data			*data;
	int				*pfd;
	int				*pid;
	struct s_proc	*next;
}	t_proc;

typedef	struct s_shell
{
	int		sig;
	char	**env;
	char	**path;
	t_proc	*process;
}	t_shell;

void		free_strs(char **s);
void		free_node(t_data *in);
void		free_tokens(t_tokens *t);
void		free_data(t_data *d);
void		free_proc(t_proc *p);
void		free_all(t_shell *s);
int			ft_checkset(char const s, char const *set);
void		*errmsg(int e);
void		*errmsg_errno(int e);
void		*sp_errmsg(int e, char *msg);
int			parse_info(char *input, t_shell *s);
char		*do_expansion(char *input);
t_tokens	*ft_split_tokens(char *input);
int			do_bash(t_shell *s);
int			fork_process(t_data *d, t_shell *s, int *pfd, int index);
int			cycle_here_doc(t_data *d, t_proc *p, int index, int *sig);
int			cycle_files(t_data *d, int fd[2]);
int			redirect_in_out(int fd[2], t_proc *p, int index);
int			clean_all_pipes(int *pfd, int lim);
char		*check_valid_cmd(char **cmd, char **path);

void	dev_print_tokens(t_tokens *t);
void	dev_print_data(t_data *d);
void	dev_print_proc(t_proc *p);

#endif