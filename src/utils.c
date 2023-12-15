/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:15:42 by ivalimak          #+#    #+#             */
/*   Updated: 2023/12/13 16:11:25 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

char	**createcmd(const char *cmd, const char **env)
{
	size_t	i;
	char	**out;
	char	*path;

	i = 0;
	out = ft_splitstrs(cmd, ' ');
	if (!out)
	{
		perror("pipex");
		exit(E_ALLOC);
	}
	path = NULL;
	while (env[i] && !path)
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0 && ft_strlen(env[i]) > 5)
			path = find((const char **)out,
					(const char **)ft_split(env[i] + 5, ':'));
		i++;
	}
	if (path && env[i])
	{
		free(out[0]);
		out[0] = path;
	}
	return (out);
}

char	*find(const char **cmd, const char **path)
{
	size_t	i;
	char	*tmp;

	if (!path)
		return (NULL);
	i = 0;
	tmp = ft_strsjoin(path[i++], cmd[0], '/');
	while (path[i] && tmp)
	{
		if (access(tmp, X_OK) == 0)
		{
			ft_freestrs((char **)path);
			return (tmp);
		}
		free(tmp);
		tmp = ft_strsjoin(path[i++], cmd[0], '/');
	}
	ft_freestrs((char **)path);
	if (!tmp)
	{
		ft_freestrs((char **)cmd);
		perror("pipex");
		exit(E_ALLOC);
	}
	return (ft_strdup(cmd[0]));
}

void	checkcmd(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (cmd->env[i])
	{
		if (ft_strncmp(cmd->env[i], "PATH", 4) == 0)
			break ;
		i++;
	}
	if (access(cmd->argv[0], X_OK) != 0)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": ", 2);
		if (cmd->env[i] && ft_strlen(cmd->env[i]) > 5)
			ft_putendl_fd("command not found", 2);
		else
			perror(NULL);
	}
}

int	openio(t_cmd *cmd)
{
	int	fd;

	fd = -2;
	if (cmd->hdoc == 0)
	{
		if (cmd->infile)
			fd = open(cmd->infile, O_RDONLY);
		if (cmd->outfile)
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else
	{
		if (cmd->infile)
			fd = get_doc(cmd->infile, open(TMPFNAME, O_WRONLY | O_CREAT, 0644));
		if (cmd->outfile)
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (fd == -1)
		openerror(cmd->infile, cmd->outfile);
	return (fd);
}

int	get_doc(const char *limiter, int fd)
{
	char	*line;

	if (fd < 0)
		exit (openerror(TMPFNAME, NULL));
	ft_printf("> ");
	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
		ft_printf("> ");
		line = get_next_line(0);
	}
	close(fd);
	fd = open(TMPFNAME, O_RDONLY);
	if (fd < 1)
		exit(openerror(TMPFNAME, NULL));
	unlink(TMPFNAME);
	return (fd);
}
