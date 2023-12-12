/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subescstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:41:02 by ivalimak          #+#    #+#             */
/*   Updated: 2023/12/11 19:11:00 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_subescstr(char const *s, unsigned int start, size_t len)
{
	char	*out;
	char	*tmp;
	size_t	slen;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	slen = ft_strlen(&s[start]);
	if (len > slen)
		len = slen;
	tmp = ft_calloc(len + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	ft_strlcpy(tmp, &s[start], len + 1);
	out = ft_strremove(tmp, '\\');
	free(tmp);
	return (out);
}
