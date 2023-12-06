/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:15:57 by ivalimak          #+#    #+#             */
/*   Updated: 2023/12/06 17:17:57 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	puterrline(char **line);

void	checkerrpipe(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(line, "/bin/sh", 7) == 0)
		{
			if (puterrline(ft_split(line, ' ')) < 0)
				return ;
		}
		else
			ft_putstr_fd(line, 2);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static int	puterrline(char **line)
{
	size_t	i;

	if (!line)
	{
		perror("pipex");
		return (-1);
	}
	i = 1;
	ft_putstr_fd("pipex: ", 2);
	while (line[i])
	{
		ft_putstr_fd(line[i++], 2);
		if (line[i])
			ft_putchar_fd(' ', 2);
	}
	freestrs(line);
	return (0);
}

int	openerror(char *fname)
{
	ft_putstr_fd("pipex: ", 2);
	perror(fname);
	return (E_OPEN);
}

int	pipeerror(void)
{
	perror("pipex");
	return (E_PIPE);
}
