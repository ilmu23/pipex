/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:04:42 by ivalimak          #+#    #+#             */
/*   Updated: 2023/12/05 16:11:49 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	char	**cmd1;
//	char	**cmd2;

	(void)argc;
//	if (argc != 5)
//		return (1);
	cmd1 = parsecmd(argv[2], argv[1]);
	if (!cmd1)
		return (2);
//	cmd2 = ft_split(argv[3], ' ');
//	if (!cmd2)
//	{
//		freestrs(cmd1);
//		return (2);
//	}
	exec(cmd1);
//	freestrs(cmd1);
//	freestrs(cmd2);
	return (0);
}
