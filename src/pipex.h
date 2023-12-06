/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:05:25 by ivalimak          #+#    #+#             */
/*   Updated: 2023/12/06 17:37:03 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/errno.h>
# define E_OPEN 1
# define E_PIPE 2
# define E_ARGS 5

typedef struct s_pipe
{
	int	pipein[2];
	int	pipeout[2];
	int	pipeerr[2];
}	t_pipe;

// pipe.c
int		ft_pipe(int argc, char **argv);
int		ft_exec(char *cmd, t_pipe stdpipe, int *status);
int		execfork(int *status, char **argv, t_pipe stdpipe);

// error.c
void	checkerrpipe(int fd);
int		openerror(char *fname);
int		pipeerror(void);

// utils.c
char	**createcmd(char *cmd);
void	closepipe(int *pipe);
void	freestrs(char **arr);
void	writefile(int fd, char *fname);
int		fillpipe(int pfd, int fd);

#endif
