/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 18:52:59 by ivalimak          #+#    #+#             */
/*   Updated: 2023/11/20 19:34:26 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	putprefix(int spaces, int *sign, int *flags);

int	ft_hexlen(unsigned long n)
{
	int	digits;

	digits = 1;
	while (n > 15)
	{
		n /= 16;
		digits++;
	}
	return (digits);
}

int	putpadding(int spaces, char c, int *sign, int *flags)
{
	int	ret;
	int	out;

	out = 0;
	ret = 0;
	if (flags[2] == 0 && spaces >= 0 && c == '0' && flags[5] > 0)
		spaces++;
	if (*sign >= 0 && c == '0' && flags[2] == 0 && flags[3] == -1)
		spaces--;
	else if (flags[2] > flags[3] && c == ' ' && flags[5] > 0 && *sign < 0)
		spaces++;
	if (c == '0' && (*sign < 0 || flags[4] > 0 || flags[5] > 0))
	{
		ret = putprefix(spaces, sign, flags);
		out += ret;
	}
	while (spaces > 0 && ret >= 0)
	{
		ret = ft_putchar_fd(c, 1);
		out += ret;
		spaces--;
	}
	if (ret < 0)
		return (-1);
	return (out);
}

static int	putprefix(int spaces, int *sign, int *flags)
{
	if (*sign < 0 && spaces > 0)
	{
		*sign = *sign * -1;
		return (ft_putchar_fd('-', 1));
	}
	if (flags[4] == 1)
	{
		flags[4] = 0;
		return (ft_putstr_fd("0x", 1));
	}
	if (flags[4] == 2)
	{
		flags[4] = 0;
		return (ft_putstr_fd("0X", 1));
	}
	if (flags[5] == 1 && *sign >= 0)
		return (ft_putchar_fd('+', 1));
	if (flags[5] == 2 && *sign >= 0)
		return (ft_putchar_fd(' ', 1));
	return (0);
}
