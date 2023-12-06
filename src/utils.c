/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:15:42 by ivalimak          #+#    #+#             */
/*   Updated: 2023/12/06 14:43:32 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**createcmd(char *cmd)
{
	size_t	i;
	char	**out;

	out = malloc(4 * sizeof(char *));
	if (!out)
		return (NULL);
	i = 0;
	out[i] = ft_strdup("/bin/sh");
	if (!out[i++])
	{
		free(out);
		return (NULL);
	}
	out[i] = ft_strdup("-c");
	if (!out[i++])
	{
		free(out[0]);
		free(out);
		return (NULL);
	}
	out[i++] = cmd;
	out[i] = NULL;
	return (out);
}

void	closepipe(int *pipe)
{
	close(pipe[0]);
	close(pipe[1]);
}

void	freestrs(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	writefile(int fd, char *fname)
{
	char	*line;
	int		outfd;

	outfd = open(fname, O_CREAT | O_TRUNC | O_WRONLY, 00644);
	if (outfd < 0)
		exit(openerror(fname));
	line = get_next_line(fd);
	while (line)
	{
		ft_putstr_fd(line, outfd);
		free(line);
		line = get_next_line(fd);
	}
}

int	fillpipe(int pfd, int fd)
{
	char	*tmp;

	tmp = get_next_line(fd);
	while (tmp)
	{
		write(pfd, tmp, ft_strlen(tmp));
		free(tmp);
		tmp = get_next_line(fd);
	}
	return (0);
}
