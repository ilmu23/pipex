/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:39:17 by ivalimak          #+#    #+#             */
/*   Updated: 2023/12/05 16:10:06 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	exec(char **cmd)
{
	pid_t	cmdpid;
	int		status;
	int		rv;

	cmdpid = fork();
	if (cmdpid == 0)
	{
		rv = execve(cmd[0], cmd, NULL);
		if (rv == -1)
			return (-1);
	}
	wait(&status);
	if (WIFEXITED(status) != 1 || WEXITSTATUS(status) != 0)
	{
		perror("Error");
		return (-1);
	}
	return (0);
}
