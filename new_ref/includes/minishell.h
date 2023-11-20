/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:32:39 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/20 16:40:11 by jngerng          ###   ########.fr       */
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
# define GREEN "\33[0;32m"
# define BLUE "\33[0;34m"
# define RESET "\33[0m"
# define FILES 15
# define LOGIC 96
# define OPERATORS 112
# define BRACKETS 384
// typedef struct s_index
// {
// 	int	index1;
// 	int	index2;
// }	t_index;

// typedef struct s_loop
// {
// 	int		iter;
// 	int		begin;
// 	char	sig;
// 	char	*input;
// }	t_loop;

/*
FILES here_doc | read | write | append
OPERATORS pipe | or | and
LOGIC or | and
BRACKETS start_b | end_b
' 34
" 39
*/
enum	e_token
{
	here_doc = 1,
	_read = 2,
	_write = 4,
	_append = 8,
	pipe = 16,
	_or = 32,
	_and = 64,
	start_b = 128,
	end_b = 256
}	;

typedef struct s_token
{
	char			*token;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_buffer
{
	int				size;
	t_token			*cmd;
	struct s_buffer	*next;
}	t_buffer;

typedef struct s_proc
{
	char			**cmd;
	t_token			*here_doc;
	t_token			*f_read;
	t_token			*f_out;
	char			out;
	char			in;
	struct s_proc	*next;
}	t_proc;

typedef struct s_block
{
	int		num;
	int		add;
	int		lim;
	int		ref;
	t_proc	*proc;
	int		*pfd;
	int		*pid;
}	t_block;

typedef struct s_root
{
	char	*root_msg;
	char	*prompt;
	char	directory[4097];
	char	change;
}	t_root;

typedef struct s_shell
{
	int		status;
	int		input;
	int		ext_code;
	char	**env;
	char	**path;
	t_block	*input;
	t_root	root;
	t_block	process_section;
}	t_shell;

int		ft_checkset(char const s, char const *set);
int		pass_space(char *input, int start);
char	*get_env(char **env, char *var, int len);
char	*get_input(t_shell *s, char *prompt);
int		int_strchr(char *s, char c);
void	free_strs(char **s);
void	free_token(t_token *t);
void	free_tokens(t_token *t);
void	free_process(t_proc *p);
void	free_processes(t_proc *p);
void	free_block(t_block *b);
void	free_process_section(t_shell *s);
void	free_all(t_shell *s);
void	*errmsg(int e);
void	*errmsg_var(int e, char *msg, int len);
void	*errmsg_token(int token);
void	*errmsg_errno(int e);
void	handle_error(t_shell *s, int ext_code);
int		shell_init(t_shell *s);
int		msg_init(t_root *msg);
int		check_logical_operator(char *input, int *index);
int		check_redirection(char *input, int *index);
int		iter_token(char *input, int i, int *new);
int		check_input(char *input, int i);
// t_block	*process_input(t_shell *s, char *input);

#endif