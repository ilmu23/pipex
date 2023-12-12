/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:15:42 by ivalimak          #+#    #+#             */
/*   Updated: 2023/12/11 19:39:37 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**createcmd(const char *cmd, const char **env)
{
	size_t	i;
	char	**out;
	char	*path;

	out = ft_splitstrs(cmd, ' ');
	path = NULL;
	if (out && *env)
	{
		i = 0;
		while (env[i] && ft_strncmp(env[i], "PATH", 4) != 0)
			i++;
		path = find(out[0], (const char **)ft_split(env[i] + 5, ':'));
	}
	else if (out)
		path = try(out[0]);
	if (!path && *cmd)
	{
		if (out)
			ft_freestrs(out);
		perror("pipex");
		exit(E_ALLOC);
	}
	free(out[0]);
	out[0] = path;
	return (out);
}

char	*find(const char *cmd, const char **path)
{
	size_t	i;
	char	*tmp;

	if (!path)
		return (NULL);
	i = 0;
	tmp = ft_strsjoin(path[i++], cmd, '/');
	while (path[i] && tmp)
	{
		if (access(tmp, X_OK) == 0)
			return (tmp);
		free(tmp);
		tmp = ft_strsjoin(path[i++], cmd, '/');
	}
	return (ft_strdup(cmd));
}

char	*try(const char *cmd)
{
	char	*tmp;

	tmp = ft_strjoin("/bin/", cmd);
	if (!tmp)
		return (NULL);
	if (access(tmp, X_OK) == 0)
		return (tmp);
	free(tmp);
	tmp = ft_strjoin("/usr/local/bin/", cmd);
	if (!tmp)
		return (NULL);
	if (access(tmp, X_OK) == 0)
		return (tmp);
	free(tmp);
	tmp = ft_strjoin("/usr/bin/", cmd);
	if (!tmp)
		return (NULL);
	if (access(tmp, X_OK) == 0)
		return (tmp);
	free(tmp);
	return (ft_strdup(cmd));
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
