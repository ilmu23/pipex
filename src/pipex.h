/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:05:25 by ivalimak          #+#    #+#             */
/*   Updated: 2023/12/05 16:31:08 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

// exec.c
int		exec(char **cmd);

// cmd.c
size_t	get_argc(const char *cmd);
char	**parsecmd(const char *cmd, const char *fname);
char	**checkcmd(char **cmd, size_t argc);
char	*execname(const char *cmd);

// utils.c
void	freestrs(char **arr);

#endif
