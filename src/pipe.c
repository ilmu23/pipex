/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:39:17 by ivalimak          #+#    #+#             */
/*   Updated: 2023/12/06 17:03:47 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_pipe(int argc, char **argv)
{
	int		i;
	int		fd;
	int		status;
	t_pipe	stdpipe;

	i = 0;
	fd = open(argv[i++], O_RDONLY);
	if (fd < 0)
		openerror(argv[0]);
	while (i < argc - 1)
	{
		if (pipe(stdpipe.pipein) != 0 || pipe(stdpipe.pipeerr) != 0)
			return (pipeerror());
		fillpipe(stdpipe.pipein[1], fd);
		close(stdpipe.pipein[1]);
		close(fd);
		fd = ft_exec(argv[i++], stdpipe, &status);
		checkerrpipe(stdpipe.pipeerr[0]);
	}
	writefile(fd, argv[i]);
	close(fd);
	return (WEXITSTATUS(status));
}

int	ft_exec(char *cmd, t_pipe stdpipe, int *status)
{
	char	**argv;

	argv = createcmd(cmd);
	if (!argv)
	{
		close(stdpipe.pipein[0]);
		return (-1);
	}
	if (pipe(stdpipe.pipeout) != 0)
	{
		close(stdpipe.pipein[0]);
		freestrs(argv);
		return (-1);
	}
	return (execfork(status, argv, stdpipe));
}

int	execfork(int *status, char **argv, t_pipe stdpipe)
{
	extern char	**environ;
	pid_t		cmdpid;
	int			out;

	cmdpid = fork();
	if (cmdpid < 0)
	{
		closepipe(stdpipe.pipeout);
		close(stdpipe.pipein[0]);
		freestrs(argv);
		return (-1);
	}
	if (cmdpid == 0)
	{
		dup2(stdpipe.pipein[0], 0);
		dup2(stdpipe.pipeout[1], 1);
		dup2(stdpipe.pipeerr[1], 2);
		close(stdpipe.pipeout[0]);
		execve(argv[0], argv, environ);
	}
	out = dup(stdpipe.pipeout[0]);
	closepipe(stdpipe.pipeout);
	close(stdpipe.pipeerr[1]);
	waitpid(cmdpid, status, 0);
	return (out);
}
