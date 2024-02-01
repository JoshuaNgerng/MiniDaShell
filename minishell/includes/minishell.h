/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:32:39 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/01 11:32:46 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
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
# include "main_struct.h"
# include "libft.h"
# define GREEN "\33[0;32m"
# define BLUE "\33[0;34m"
# define RESET "\33[0m"
# define FILES 15
# define LOGIC 96
# define OPERATORS 112
# define BRACKETS 384

/*
FILES here_doc | read | write | append
LOGIC or | and
OPERATORS pipe | or | and
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

typedef struct s_fd
{
	int	read_;
	int	write_;
	int	fd_in;
	int	fd_out;
}	t_fd;

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

typedef struct s_root_ptr
{
	int		len1;
	int		len2;
	char	*tmp1;
	char	*tmp2;
}	t_root_ptr;

typedef struct s_child
{
	char	**cmd;
	char	*path_cmd;
	t_proc	*hold;
}	t_child;

typedef struct s_star
{
	int		star_pos;
	int		start;
	int		head_type;
	int		end;
	char	*str;
}	t_star;

typedef struct s_expand
{
	int		i;
	int		len;
	char	*str;
	char	*status;
	t_shell	*s;
	t_token	*list;
	t_token	*list_malloc;
}	t_expand;

extern int	g_ctrl_c;

/* free functions */

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

/* error messages */

void	errmsg_name(char *name_);
void	*errmsg(int e);
void	*errmsg_var(int e, char *msg, int len);
void	*errmsg_token(int token);
void	*errmsg_errno(int e);
void	*sp_errmsg(int e, char *msg);
void	*errmsg_expand(char *cmd, t_token *list, t_token *list_malloc);

/* handle strings */

int		ft_checkset(char const s, char const *set);
int		pass_space(char *input, int start);
int		int_strchr(char *s, char c);
int		int_strcpy(char *dst, int index, const char *src);
int		read_quo(char ref, int quo);

/* env list */

int		find_equal_sign(char *s);
void	env_list_addback(t_env **list, t_env *new);
t_env	*search_env(t_env *head, char *key, int len);
t_env	*make_env_node(char *env, int equal);
t_env	*env_list_init(char **env);
void	env_list_addback(t_env **list, t_env *new);

/* misc */

void	transfer_token_ptr(t_ptr *p, t_token *t);
void	handle_error(t_shell *s, int ext_code);
char	*get_env(char **env, char *var, int len);
char	*get_input(t_shell *s, const char *prompt);

/* handle pipes */

void	close_pipes(int *pipes, int len);
int		prepare_pipes(int *pipes, int len);
void	clear_pipes(t_processor *p);
void	clear_here_doc(t_processor *p);
char	*read_from_pipe(int fd);

/* intialize  */

int		shell_init(t_shell *s, char **av, char **env);
char	*root_init(char **env);
char	*get_prompt(char *direc, char *root);
void	handle_signal(int signum);

/* handle input */

int		complete_input(t_shell *s, t_token **head, char *r, int *c);
int		check_input(char *input, int i);
int		check_inside_loop(char *input, int i, int *prev, int *brac);
int		get_new_token(char *input, int i, int *new, int *brac);
int		iter_token(char *input, int i, int *new);
int		check_redirection(char *input, int *index);
int		check_logical_operator(char *input, int *index);

/* bash function */

int		bash(t_shell *s);
t_sect	*get_next_process(t_shell *s, t_sect *buffer, int type);
int		prepare_env_n_path(t_env *env, t_processor *p);

/* section and tokenize */

int		tokenize_and_sectioning(t_shell *s, t_processor	*p);
int		add_process(t_shell *s, t_ptr_p *ptr, t_sect *sec, int *index);
int		tokenize_input(t_shell *s, t_token **head, int *index, int *type);
int		get_bracket(char *input, int i);

/* expand */

int		expand(t_shell *s, t_sect *sect);
int		expand_here_doc(t_shell *s, t_token *t);
char	*clean_token(char *str);
void	copy_expand(char *dst, char *src, t_token *list, t_token *list_malloc);
int		search_expand(t_shell *s, t_expand *e);
int		expand_cmd(t_token *now, t_token **prev, t_shell *s, char *status);
int		expand_subshell(t_token *new, t_ptr *buffer, t_expand *e);
int		expand_star(t_token *new, t_ptr *buffer, t_expand *e);
int		read_star(t_star *s, t_token *new, int *ptr);
int		read_from_dir(t_star *s, DIR *d, t_ptr *buffer, int *len);

/* here doc */

int		do_here_doc(t_shell *s, t_processor *p);
int		loop_here_doc(t_shell *s, t_processor *p, int *pfd);

/* children process */

int		process_child(t_shell *s, t_processor *p, t_proc *hold);
int		process_builtins(t_shell *s, t_proc *p, int check);
char	**get_cmd_array(t_token *cmd);
int		find_cmd(char **path, char **path_cmd, char *cmd, int *ext_code);
int		cycle_output_files(t_token *f_out);
int		cycle_input_files(t_token *f_read);
int		dup_stdin_stdout(t_shell *s, t_processor *p, t_proc *proc);
void	dup_helper(t_processor *p, t_fd *fd, int check);

/* builtins */

int		check_builtins(const t_proc *proc);
void	builtin_errmsg_opt(char *name);
void	builtin_errmsg_arg(char *name);
int		check_options(char *cmd);
int		get_number_arg(char **cmd, int check);
int		pwd_function(t_shell *s, char **cmd);
int		cd_function(t_shell *s, char **cmd);
int		exit_function(t_shell *s, char **cmd);
int		export(t_shell *s, char **cmd);
int		unset(t_shell *s, char **cmd);
int		env_print(t_shell *s, char **cmd);

/* subshell */

void	subshell(t_shell *s, t_processor *p, t_proc *hold);

/* dev func for debug */

void	dev_print_strs(char **s);
void	dev_print_tokens(t_token *t);
void	dev_print_proc_list(t_proc *p);
void	dev_print_sect(t_sect *sec);
void	dev_print_processor(t_processor p);

#endif
