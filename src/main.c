/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:04:42 by ivalimak          #+#    #+#             */
/*   Updated: 2023/12/12 16:38:22 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	if (argc != 5)
		return (E_ARGS);
	return (ft_pipe((const size_t)argc - 1,
			(const char **)&argv[1], 0, (const char **)env));
}
