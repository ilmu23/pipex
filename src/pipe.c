/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:39:17 by ivalimak          #+#    #+#             */
/*   Updated: 2023/12/12 16:59:30 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_pipe(const size_t argc, const char **argv, const int hdoc,
	const char **env)
{
	int		status;
	t_pipe	iopipe;
	size_t	i;

	iopipe.n = (argc * 2) - 4 + (hdoc * 2);
	iopipe.pipes = malloc(iopipe.n * sizeof(int));
	if (!iopipe.pipes)
		return (pipeerror());
	i = 0;
	while (i < iopipe.n)
	{
		if (pipe(iopipe.pipes + i) != 0)
		{
			i--;
			while (i >= 0)
				close(iopipe.pipes[i--]);
			return (pipeerror());
		}
		i += 2;
	}
	execpipe(parseargs(argc, argv, hdoc, env), iopipe, &status);
	free(iopipe.pipes);
	return (WEXITSTATUS(status));
}
