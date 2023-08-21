/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:27:32 by jngerng           #+#    #+#             */
/*   Updated: 2023/05/08 19:27:32 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include "ft_printf.h"
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <string.h>

typedef struct s_pipfd
{
	int		pfd[2];
	int		fd[2];
	char	**path;
}	t_pipfd;

char	**get_path(char **env);
int		find_open(char **av, int mode);
char	*find_exe(char *cmd, char **env);
char	*handle_sp(char *cmd);
char	**get_cmd(char *cmd);
void	handle_error_exit(char *errmsg, int error);
int		handle_error_return(char *errmsg, int error);
int		error_para(char *name);
int		ft_pip_strchr(const char *s, const char *c);

#endif