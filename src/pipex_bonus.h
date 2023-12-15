/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:05:25 by ivalimak          #+#    #+#             */
/*   Updated: 2023/12/15 17:15:56 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# define E_OPEN 1
# define E_PIPE 2
# define E_ALLOC 3
# define E_ARGS 5
# define E_EXEC 127
# define TMPFNAME ".here_doc"

typedef struct s_cmd
{
	int				hdoc;
	pid_t			cmdpid;
	char			**argv;
	const char		**env;
	const char		*infile;
	const char		*outfile;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pipe
{
	int		*pipes;
	size_t	n;
}	t_pipe;

// pipe.c
int		ft_pipe(const size_t argc, const char **argv, const int hdoc,
			const char **env);

// cmd.c
t_cmd	*parseargs(const size_t argc, const char **argv, const int hdoc,
			const char **env);
t_cmd	*newcmd(const char *cmd, const int hdoc, const char **env);
char	**cmdarr(const char *cmd);
void	addcmd(t_cmd **cmds, t_cmd *new);
void	freecmds(t_cmd *cmds);

// exec.c
void	execpipe(t_cmd *cmds, t_pipe pipe, int *status);
void	execcmd(t_cmd *cmd, t_pipe iopipe, size_t i);
void	execfork(t_cmd *cmd, t_pipe iopipe, size_t i, int fd);

// error.c
void	checkerrpipe(const int fd);
int		openerror(const char *infile, const char *outfile);
int		pipeerror(void);
int		forkerror(void);

// utils.c
char	**createcmd(const char *cmd, const char **env);
char	*find(const char **cmd, const char **env);
void	checkcmd(t_cmd *cmd);
int		openio(t_cmd *cmd);
int		get_doc(const char *limiter, int fd);

#endif
