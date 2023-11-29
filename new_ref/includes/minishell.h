/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:32:39 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/29 13:23:01 by jngerng          ###   ########.fr       */
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
	_pipe = 16,
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

typedef struct s_ptr
{
	t_token	*head;
	t_token	*tail;
}	t_ptr;

typedef struct s_buffer
{
	int		size;
	t_ptr	cmd;
	t_ptr	here_doc;
	t_ptr	read;
	t_ptr	out;
}	t_buffer;

typedef struct s_proc
{
	char			**cmd;
	t_token			*here_doc;
	t_token			*f_read;
	t_token			*f_out;
	int				in;
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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_env_buffer
{
	t_env				*env;
	struct s_env_buffer	*next;
}	t_env_buffer;

typedef struct s_shell
{
	int		status;
	int		check;
	int		ext_code;
	char	*input;
	char	**env_ptr;
	char	**path;
	t_env	*env;
	t_root	root;
	t_block	process_section;
}	t_shell;

int		ft_checkset(char const s, char const *set);
int		pass_space(char *input, int start);
char	*get_env(char **env, char *var, int len);
char	*get_input(t_shell *s, char *prompt);
int		int_strchr(char *s, char c);
// int		get_end_brac(char *input, int i);
void	free_strs(char **s);
void	free_token(t_token *t);
void	free_tokens(t_token *t);
void	free_process(t_proc *p);
void	free_processes(t_proc *p);
// void	free_block(t_block *b);
void	free_process_section(t_shell *s);
void	free_reset(t_shell *s);
void	free_all(t_shell *s);
void	free_all_exit(t_shell *s, int ext_code);
void	free_env_node(t_env *env);
void	free_env_list(t_env *list);
void	*errmsg(int e);
void	*errmsg_var(int e, char *msg, int len);
void	*errmsg_token(int token);
void	*errmsg_errno(int e);
void	handle_error(t_shell *s, int ext_code);
int		shell_init(t_shell *s, char **env);
t_env	*env_list_init(char **env);
t_env	*make_env_node(char *env, int equal);
t_env	*search(t_env *head, char *key);
void	env_list_addback(t_env **list, t_env *new);
int		find_equal_sign(char *s);
int		complete_input(t_shell *s, t_token **head, char *r, int c);
int		check_logical_operator(char *input, int *index);
int		check_redirection(char *input, int *index);
int		iter_token(char *input, int i, int *new);
int		check_input(char *input, int i);
int		bash(t_shell *s);
int		do_bash(t_shell *s, int *index);
int		tokenize_input(t_shell *s, t_token **head, int *index, int *type);
int		process_init(t_shell *s, int *i, int *type);
int		expand(t_shell *s, t_buffer *b);
int		search_expand(char *str, t_env **list, int *check);
void	copy_expand(char *dst, t_env *list, char *src);
void	transfer_token_buffer(t_proc *p, t_buffer *b, \
								t_block *block, t_token *t);
int		do_processes(t_shell *s);
// t_block	*process_input(t_shell *s, char *input);

void	dev_print_tokens(t_token *t);
void	dev_print_data(t_proc *p);
# define NULL 0
#endif