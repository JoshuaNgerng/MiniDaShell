/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:47:50 by jngerng           #+#    #+#             */
/*   Updated: 2023/05/24 17:47:50 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "libft.h"
# include "ft_printf.h"
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <string.h>

/*
p_env	= pointer to env (to fit within 4 parameter)
paths	= store to path to locate commands
limit	= pointer to the limit for here_doc
pfd		= to store all the pip fd
index	= to tell the function which command 
		  it is running to fetch the right pipe fd
op		= indicate what operation it is doing (start, middle or end)
mode	= indicate whether here_doc is active or not
max		= store the max number of commands (for loop and cal)
fd_in/fd_out	= to store the fd to the right files
*/
typedef struct s_pip
{
	char	**p_env;
	char	**paths;
	char	*limit;
	int		*pfd;
	int		index;
	int		op;
	int		max;
	int		mode;
	int		fd_in;
	int		fd_out;
}	t_pip;

int		check_empty(int ac, char **av);
int		find_fd(t_pip *pip, char *file_in, char *file_out);
char	*find_exe(char *cmd, char **paths);
char	*handle_sp(char *cmd);
char	**get_cmd(char *cmd);
int		do_cmd(t_pip pip, char *in_cmd, int *pid);
int		wait_clean(t_pip pip, int *pid);
void	handle_error_exit(char *errmsg, int error);
int		handle_error_return(char *errmsg, int error);
int		error_para(char *name);
int		ft_pip_strchr(const char *s, const char *c);
void	free_exit(t_pip pip, char *exe, char **cmd, int *pid);

#endif