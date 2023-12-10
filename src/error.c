/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:15:57 by ivalimak          #+#    #+#             */
/*   Updated: 2023/12/10 14:51:51 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	puterrline(char **line);

void	checkerrpipe(const int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(line, "/", 1) == 0)
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
	ft_putstr_fd(ft_strrchr(line[0], '/') + 1, 2);
	ft_putchar_fd(' ', 2);
	while (line[i])
	{
		ft_putstr_fd(line[i++], 2);
		if (line[i])
			ft_putchar_fd(' ', 2);
	}
	ft_freestrs(line);
	return (0);
}

int	openerror(const char *infile, const char *outfile)
{
	ft_putstr_fd("pipex: ", 2);
	if (infile)
		perror(infile);
	else
		perror(outfile);
	return (E_OPEN);
}

int	pipeerror(void)
{
	perror("pipex");
	return (E_PIPE);
}

int	forkerror(void)
{
	perror("pipex");
	return (E_EXEC);
}
