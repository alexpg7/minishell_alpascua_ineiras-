/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printtype.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:56:42 by alpascua          #+#    #+#             */
/*   Updated: 2025/01/12 16:33:22 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_printchar(char c)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	return (1);
}

int	ft_numlen(unsigned long num, unsigned long base)
{
	int	i;

	i = 0;
	while (num / base != 0)
	{
		num = num / base;
		i++;
	}
	return (i + 1);
}

int	ft_printbase(unsigned long nbr, char *base, unsigned long len)
{
	int	flag;

	flag = 0;
	if (nbr >= len)
	{
		if (ft_printbase(nbr / len, base, len) == -1)
			return (-1);
	}
	flag = ft_printchar(base[nbr % len]);
	if (flag == -1)
		return (-1);
	return (1);
}

int	ft_printstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_printstr("(null)"));
	while (*str)
	{
		if (ft_printchar(*str) == -1)
			return (-1);
		str++;
		i++;
	}
	return (i);
}

int	ft_printpointer(int long long ptr)
{
	int	count;

	count = 0;
	if (!ptr)
	{
		if (ft_printstr("(nil)") == -1)
			return (-1);
		return (5);
	}
	if (ptr == LONG_MIN)
	{
		if (ft_printstr("0x") == -1 || ft_printstr("8000000000000000") == -1)
			return (-1);
		return (18);
	}
	else if (ft_printstr("0x") == -1)
		return (-1);
	count = ft_printbase(ptr, "0123456789abcdef", 16);
	if (count == -1)
		return (-1);
	count = ft_numlen(ptr, 16);
	return (2 + count);
}
