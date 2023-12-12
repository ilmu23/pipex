/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:28:55 by ivalimak          #+#    #+#             */
/*   Updated: 2023/12/11 19:54:24 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*parseargs(const size_t argc, const char **argv, const int hdoc,
	const char **env)
{
	size_t	i;
	t_cmd	*head;
	t_cmd	*new;

	i = 1;
	head = NULL;
	while (i < argc - 1)
	{
		new = newcmd(argv[i], hdoc, env);
		if (!new)
		{
			if (head)
				freecmds(head);
			perror("pipex");
			exit(E_ALLOC);
		}
		addcmd(&head, new);
		i++;
	}
	head->infile = argv[0];
	new->outfile = argv[argc - 1];
	return (head);
}

t_cmd	*newcmd(const char *cmd, const int hdoc, const char **env)
{
	t_cmd	*out;

	out = malloc(sizeof(t_cmd));
	if (!out)
		return (NULL);
	if (!*cmd)
		out->argv = cmdarr(cmd);
	else
		out->argv = createcmd(cmd, env);
	if (!out->argv)
	{
		free(out);
		return (NULL);
	}
	out->env = env;
	out->hdoc = (int)hdoc;
	out->next = NULL;
	out->infile = NULL;
	out->outfile = NULL;
	out->cmdpid = 0;
	return (out);
}

char	**cmdarr(const char *cmd)
{
	char	**out;

	out = malloc(2 * sizeof(char *));
	if (!out)
		return (NULL);
	out[0] = ft_strdup(cmd);
	out[1] = NULL;
	return (out);
}

void	addcmd(t_cmd **cmds, t_cmd *new)
{
	t_cmd	*tmp;

	if (!(*cmds))
	{
		*cmds = new;
		return ;
	}
	tmp = *cmds;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	freecmds(t_cmd *cmds)
{
	t_cmd	*prev;

	while (cmds)
	{
		ft_freestrs(cmds->argv);
		prev = cmds;
		cmds = cmds->next;
		free(prev);
	}
}
