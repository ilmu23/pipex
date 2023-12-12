/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:52:50 by ivalimak          #+#    #+#             */
/*   Updated: 2023/12/11 17:42:48 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execpipe(t_cmd *cmds, t_pipe iopipe, int *status)
{
	size_t	i;
	t_cmd	*start;

	i = 0;
	start = cmds;
	if (pipe(iopipe.pipes) != 0)
		exit(pipeerror());
	while (cmds)
	{
		execcmd(cmds, iopipe, i);
		i += 2;
		cmds = cmds->next;
	}
	cmds = start;
	while (cmds)
	{
		waitpid(cmds->cmdpid, status, 0);
		cmds = cmds->next;
	}
	close(iopipe.pipes[1]);
	checkerrpipe(iopipe.pipes[0]);
	freecmds(start);
}

void	execcmd(t_cmd *cmd, t_pipe iopipe, size_t i)
{
	int				fd;

	fd = openio(cmd);
	if (fd == -1 && cmd->outfile)
		exit(E_OPEN);
	if (fd != -1 && access(cmd->argv[0], X_OK) != 0
		&& (*(cmd->argv[0]) || !cmd->next || *(cmd->next->argv[0])))
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putendl_fd(": command not found", 2);
	}
	cmd->cmdpid = fork();
	if (cmd->cmdpid < 0)
		exit(forkerror());
	if (cmd->cmdpid == 0)
		execfork(cmd, iopipe, i, fd);
	if (cmd->infile && fd >= 0)
		close(fd);
	else
		close(iopipe.pipes[i]);
	if (cmd->outfile && fd >= 0)
		close(fd);
	else
		close(iopipe.pipes[i + 3]);
}

void	execfork(t_cmd *cmd, t_pipe iopipe, size_t i, int fd)
{
	if (fd >= 0 && cmd->infile)
		dup2(fd, 0);
	else if (cmd->infile)
		close(0);
	else
		dup2(iopipe.pipes[i], 0);
	if (fd >= 0 && cmd->outfile && cmd->hdoc != 2)
		dup2(fd, 1);
	else if (!cmd->outfile)
		dup2(iopipe.pipes[i + 3], 1);
	dup2(iopipe.pipes[1], 2);
	if (fd >= 0)
		close(fd);
	i = 0;
	while (i < iopipe.n)
		close(iopipe.pipes[i++]);
	if (fd == -1)
		return ;
	execve(cmd->argv[0], cmd->argv, (char **)cmd->env);
	exit (E_EXEC);
}
