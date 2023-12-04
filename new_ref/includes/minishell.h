/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:32:39 by jngerng           #+#    #+#             */
/*   Updated: 2023/12/04 22:09:29 by jngerng          ###   ########.fr       */
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
	t_ptr	cmd;
	t_ptr	here_doc;
	t_ptr	read;
	t_ptr	out;
}	t_buffer;

typedef struct s_proc
{
	t_token			*cmd;
	t_token			*here_doc;
	t_token			*f_read;
	t_token			*f_out;
	int				in;
	struct s_proc	*next;
}	t_proc;

typedef struct s_sect
{
	t_proc			*block;
	int				pid;
	int				operator;
	struct s_sect	*next;
}	t_sect;

typedef struct s_processor
{
	int		here_doc_num;
	int		pipe_num;
	int		index_h;
	int		index_p;
	t_sect	*buffer;
	int		*here_doc_pipe;
	int		*pid;
	int		*pipe;
}	t_processor;

typedef struct s_ptr_p
{
	t_proc	*head;
	t_proc	*tail;
}	t_ptr_p;

typedef struct s_ptr_s
{
	t_sect	*head;
	t_sect	*tail;
}	t_ptr_s;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_root
{
	char	*root_msg;
	char	*prompt;
	t_env	*pwd;
	t_env	*oldpwd;
	char	directory[4097];
	char	change;
}	t_root;

typedef struct s_shell
{
	int			status;
	int			check;
	int			ext_code;
	char		*input;
	char		**env_ptr;
	char		**path;
	t_env		*env;
	t_root		root;
	t_processor	processor;
}	t_shell;

int		ft_checkset(char const s, char const *set);
int		pass_space(char *input, int start);
char	*get_env(char **env, char *var, int len);
char	*get_input(t_shell *s, char *prompt);
int		int_strchr(char *s, char c);
int		strcpy_index(char *dst, int start, char *src);
void	close_pipes(int *pipes, int len);
int		prepare_pipes(int *pipes, int len);
int		strcpy_index(char *dst, int start, char *src);
// int		get_end_brac(char *input, int i);
void	free_strs(char **s);
void	free_token(t_token *t);
void	free_tokens(t_token *t);
void	free_tokens_empty(t_token *t);
void	free_process(t_proc *p);
void	free_processes(t_proc *p);
void	free_sect(t_sect *sec);
void	free_sect_list(t_sect *list);
void	free_reset(t_shell *s);
void	free_all(t_shell *s);
void	free_all_exit(t_shell *s, int ext_code);
void	free_env_node(t_env *env);
void	free_env_list(t_env *list);
void	*errmsg(int e);
void	*errmsg_var(int e, char *msg, int len);
void	*errmsg_token(int token);
void	*errmsg_errno(int e);
void	*sp_errmsg(int e, char *msg);
void	handle_error(t_shell *s, int ext_code);
int		shell_init(t_shell *s, char **env);
t_env	*env_list_init(char **env);
t_env	*make_env_node(char *env, int equal);
t_env	*search_env(t_env *head, char *key, int len);
void	env_list_addback(t_env **list, t_env *t_new);
int		export(t_shell *s, char **cmd);
int		unset(t_shell *s, char **cmd);
int		find_equal_sign(char *s);
int		read_quo(char ref, int quo);
int		complete_input(t_shell *s, t_token **head, char *r, int c);
int		check_logical_operator(char *input, int *index);
int		check_redirection(char *input, int *index);
int		iter_token(char *input, int i, int *t_new);
int		check_input(char *input, int i);
int		bash(t_shell *s);
int		do_bash(t_shell *s, int *index);
int		tokenize_input(t_shell *s, t_token **head, int *index, int *type);
void	transfer_token_ptr(t_ptr *p, t_token *t);
// section
int		tokenize_and_sectioning(t_shell *s, t_processor	*p);
//
int		add_process(t_shell *s, t_ptr_p *ptr, t_sect *sec, int *index);
// here doc
int		get_here_doc_num_proc(t_proc *p);
int		do_here_doc(t_shell *s, t_processor *p);
int		loop_here_doc(t_shell *s, t_processor *p, int *pfd);
//expand
int		expand_here_doc(t_shell *s, t_token *t);
int		copy_expand(char *dst, char *src, t_token *list, int file);
int		search_expand(char *str, t_env *env, t_token **list, int *len);
int		expand_cmd(t_token *now, t_token **prev, t_shell *);
int		expand(t_shell *s, t_sect *sect);
// fork
int		process_child(t_shell *s, t_processor *p, t_proc *hold);
// files
int		cycle_output_files(t_token *f_out);
int		cycle_input_files(t_token *f_read);
//cmd
char	**get_cmd_array(t_token *cmd);
int		find_cmd(char **path, char **path_cmd, char *cmd, int *ext_code);
//utlis
void	handle_signal(int signum);
void	detach_node(t_env **head, t_env *target);
// builtin
int		check_special_process(t_shell *s, t_proc *proc);

// void	dev_print_tokens(t_token *t);
// void	dev_print_data(t_proc *p);
# define NULL ((void *)0)
#endif