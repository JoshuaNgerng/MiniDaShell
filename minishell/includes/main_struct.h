/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 04:13:56 by jngerng           #+#    #+#             */
/*   Updated: 2024/02/07 11:50:18 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_STRUCT_H
# define MAIN_STRUCT_H
# include <termios.h>

typedef struct s_token
{
	char			*token;
	int				type;
	struct s_token	*next;
}	t_token;

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
	int		stdin_;
	int		stdout_;
	t_sect	*buffer;
	int		*here_doc_pipe;
	int		*pid;
	int		*pipe;
	char	**path;
	char	**env;
}	t_processor;

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
	char	*pwd;
	char	change;
}	t_root;

typedef struct s_shell
{
	int				status;
	int				check;
	int				subshell_status;
	int				input_len;
	char			*input;
	t_env			*env;
	t_root			root;
	int				(*builtin[7])(struct s_shell *, char **);
	struct termios	termios_;
	t_processor		processor;
}	t_shell;

// #define NULL ((void *) 0)
#endif