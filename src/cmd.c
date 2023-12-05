/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:30:37 by ivalimak          #+#    #+#             */
/*   Updated: 2023/12/05 16:30:49 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	get_argc(const char *cmd)
{
	size_t	argc;

	argc = 0;
	while (*cmd)
	{
		while (*cmd == ' ' && *cmd)
			cmd++;
		if (*cmd)
			argc++;
		while (*cmd != ' ' && *cmd)
			cmd++;
	}
	return (argc);
}

char	**parsecmd(const char *cmd, const char *fname)
{
	size_t	i;
	char	**out;
	char	**tmp;

	out = malloc((get_argc(cmd) + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	tmp = ft_split(cmd, ' ');
	if (!tmp)
	{
		free(out);
		return (NULL);
	}
	i = 1;
	out[0] = execname(tmp[0]);
	while (tmp[i])
	{
		out[i] = ft_strdup(tmp[i]);
		i++;
	}
	out[i++] = (char *)fname;
	freestrs(tmp);
	out[i] = NULL;
	return (checkcmd(out, i - 1));
}

char	**checkcmd(char **cmd, size_t argc)
{
	size_t	i;

	i = 0;
	while (i < argc)
	{
		if (!cmd[i])
		{
			i = 0;
			break ;
		}
		i++;
	}
	if (i == argc)
		return (cmd);
	i = 0;
	while (i < argc)
	{
		if (cmd[i])
			free(cmd[i]);
		i++;
	}
	return (NULL);
}

char	*execname(const char *cmd)
{
	char	*tmp;

	tmp = ft_strrchr(cmd, '/');
	if (tmp)
		return (ft_strdup(cmd));
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	tmp = ft_strjoin("/usr/bin/", cmd);
	if (!tmp)
		return (NULL);
	if (access(tmp, F_OK) == 0)
		return (tmp);
	free(tmp);
	return (ft_strjoin("/bin/", cmd));
}
