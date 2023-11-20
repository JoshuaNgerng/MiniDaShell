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

typedef struct s_iter
{
	int	i;
	int	j;
}	t_iter;

typedef	struct s_list
{
	char			*str;
	struct s_list	*next;
}	t_list;

typedef struct s_s_list
{
	t_list	*start;
	t_list	*end;
}	t_t_list;

typedef struct s_nest
{
	int				nesting;
	int				operator;
	struct s_nest	*prev;
	struct s_nest	*next;
}	t_nest;

typedef struct s_nest_check
{
	t_nest	*start;
	t_nest	*end;
}	t_nest_check;


typedef	struct s_buffer
{
	int			i;
	t_t_list	nodes;
}	t_buffer;

typedef struct s_token
{
	char			*token;
	char			type;
	struct s_token	*next;
}	t_token;

typedef struct s_token_ptr
{
	t_token	*sent_to_proc;
	t_token	*remainder;
}	t_token_ptr;

typedef struct s_token_buffer
{
	int		size;
	t_token	*cmd_start;
	t_token *cmd_end;
	t_token	*remainder;
}	t_token_buffer;

// typedef struct s_paranthesis
// {
// 	int	
// }	t_paranthesis;


/*
every partion have one cmd
only one active input file nearest to a cmd (however it still detects other input file)
create all output file but only further file is writen into
*/

// change file system struct
typedef struct s_data
{
	char			**cmd;
	t_token			*f_read;
	t_token			*here_doc;
	t_token			*f_out;
	char			out;
	char			in;
	struct s_data	*next;
}	t_data;

typedef struct s_proc
{
	int		num;
	int		add;
	int		lim;
	int		ref;
	t_data	*data;
	int		*pfd;
	int		*pid;
}	t_proc;

typedef	struct s_shell
{
	int		status;
	char	*root;
	char	**env;
	char	**path;
	t_token	*input;
	t_proc	process;
}	t_shell;

void	free_strs(char **s);
void	free_nest_list(t_nest *start);
void	free_list(t_list *t);
void	free_node(t_data *node);
void	free_token(t_token *t);
void	free_tokens(t_token *t);
void	free_data(t_data *d);
void	free_proc(t_shell *s);
void	free_all(t_shell *s);
char	*get_env(char **env, char *var, int len);
int		ft_checkset(char const s, char const *set);
int		pass_space(char *input, int start);
void	*errmsg(int e);
void	*errmsg_var(int e, char *msg, int len);
void	*errmsg_errno(int e);
void	*sp_errmsg(int e, char *msg);
int		ext_code(void);

void	split_tokens(char *input, t_shell *s);
void	handle_err_input(t_shell *s, int exit_code);
char	check_logical_operator(char *input, int *index);
char	check_redirection(char *input, int *index);
int		unexpected_token_err(char *input, int index);
int		do_bash(t_shell *s);
int		proc_init(t_token *t, t_shell *s);

/*
void	free_strs(char **s);
void	free_list(t_list *t);
// void	free_list(t_tmp	*list, char f);
void	free_node(t_data *node);
void	free_tokens(t_token *t);
void	free_data(t_data *d);
void	free_proc(t_shell *s);
void	free_all(t_shell *s);
char	*get_env(char **env, char *var, int len);
int		ft_checkset(char const s, char const *set);
int		pass_space(char *input, int start);
void	*errmsg(int e);
void	*errmsg_var(int e, char *msg, int len);
void	*errmsg_errno(int e);
void	*sp_errmsg(int e, char *msg);

int		get_input(t_shell *s);
char	check_input(char *r, char check);

int		parse_info(char *input, t_shell *s);
char	check_logical_operator(char *input, int *index);
char	check_redirection(char *input, int *index);

char	*do_expansion(char *input, char **env);
// char	check_quo(char *input);
t_list	*iter_input_list(char *input, char **env, t_tmp *add, int *len);
int	ft_split_tokens(char *input, t_shell *s);
int		do_bash(t_shell *s);
int		fork_process(t_data *d, t_shell *s, t_proc *p, int index);
int		cycle_here_doc(t_data *d, t_proc *p, int index, int *sig);
int		cycle_files(t_data *d, int fd[2]);
int		redirect_in_out(int fd[2], t_proc *p, int index);
int		clean_all_pipes(int *pfd, int lim);
char	*check_valid_cmd(char *cmd, char **path);

void	dev_print_tokens(t_token *t);
void	dev_print_data(t_data *d);
void	dev_print_proc(t_proc *p);
*/

#endif