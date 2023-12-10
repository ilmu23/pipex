/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitstrs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:02:23 by ivalimak          #+#    #+#             */
/*   Updated: 2023/12/10 14:37:56 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	getsplits(char const *s, char c);
static size_t	getstrend(char const *s, size_t i, const char c);
static char		*makesplit(char const *s, char c);

char	**ft_splitstrs(char const *s, char c)
{
	char	**out;
	size_t	splits;
	size_t	i;

	if (!s)
		return (NULL);
	splits = getsplits(s, c);
	out = ft_calloc((splits + 1), sizeof(char *));
	if (!out)
		return (NULL);
	i = 0;
	while (i <= splits)
	{
		out[i++] = makesplit(s, c);
		if (!out[i - 1] && i <= splits)
		{
			while (i > 0)
				free(out[i-- - 1]);
			free(out);
			return (NULL);
		}
	}
	return (out);
}

static size_t	getsplits(char const *s, char c)
{
	size_t	i;
	size_t	splits;

	if (!c && !*s)
		return (0);
	i = 0;
	splits = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			i = getstrend(s, i + 1, s[i]);
			splits++;
			continue ;
		}
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c
			&& s[i] != '\'' && s[i] != '"')
			i++;
		if (s[i - 1] != c)
			splits++;
	}
	return (splits);
}

static size_t	getstrend(char const *s, size_t i, const char c)
{
	while (s[i] && s[i] != c)
		i++;
	if (s[i])
		i++;
	return (i);
}

static char	*makesplit(char const *s, char c)
{
	static size_t	i = 0;
	size_t			j;

	if (s[i] == '\'' || s[i] == '"')
	{
		j = i + 1;
		i = getstrend(s, i + 1, s[i]);
		return (ft_substr(s, j, i - 1 - j));
	}
	while (s[i] && s[i] == c)
		i++;
	j = i;
	if (s[i] == '\'' || s[i] == '"')
		return (makesplit(s, c));
	while (s[i] && s[i] != c)
		i++;
	if (j == i)
	{
		i = 0;
		return (NULL);
	}
	return (ft_substr(s, j, i - j));
}
