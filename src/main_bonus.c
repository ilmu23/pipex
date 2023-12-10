/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:04:42 by ivalimak          #+#    #+#             */
/*   Updated: 2023/12/09 20:36:22 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **env)
{
	int	hdoc;

	hdoc = 0;
	if (argc < 5)
		return (E_ARGS);
	if (strncmp(argv[1], "here_doc", 8) == 0)
		hdoc = 1;
	return (ft_pipe((const size_t)argc - 1 - hdoc,
			(const char **)&argv[1 + hdoc], hdoc, (const char **)env));
}
