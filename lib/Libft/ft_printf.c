/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:51:08 by alpascua          #+#    #+#             */
/*   Updated: 2025/01/29 11:17:12 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_isin(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_format3(va_list list, char c)
{
	int				flag;
	int long long	num;

	flag = 0;
	if (c == 'u')
	{
		num = va_arg(list, unsigned int);
		if (ft_printbase(num, "0123456789", 10) == -1)
			return (-1);
		flag = ft_numlen((int long long)num, 10);
	}
	else if (c == 'x' || c == 'X')
	{
		num = va_arg(list, unsigned int);
		if (c == 'x')
			flag = ft_printbase(num, "0123456789abcdef", 16);
		else if (c == 'X')
			flag = ft_printbase(num, "0123456789ABCDEF", 16);
		if (flag == -1)
			return (-1);
		flag = ft_numlen((int long long)num, 16);
	}
	if (flag == -1)
		return (-1);
	return (flag);
}

static int	ft_format2(va_list list, char c)
{
	int				flag;
	int				extra;
	int long long	num;

	flag = 0;
	extra = 0;
	if (c == 'i' || c == 'd')
	{
		num = va_arg(list, int);
		if (num < 0)
		{
			if (ft_printchar('-') == -1)
				return (-1);
			num = (int long long)(-num);
			extra = 1;
		}
		num = (int long long)num;
		if (ft_printbase(num, "0123456789", 10) == -1)
			return (-1);
		flag = ft_numlen((int long long)num, 10);
	}
	if (flag == -1)
		return (-1);
	return (flag + extra);
}

static int	ft_format(va_list list, char c)
{
	if (c == 'c')
		return (ft_printchar(va_arg(list, int)));
	else if (c == 's')
		return (ft_printstr(va_arg(list, char *)));
	else if (c == 'p')
		return (ft_printpointer(va_arg(list, int long long)));
	else if (c == '%')
		return (ft_printchar('%'));
	else if (c == 'i' || c == 'd')
		return (ft_format2(list, c));
	return (ft_format3(list, c));
}

int	ft_printf(char const *format, ...)
{
	va_list		list;
	int			count;
	int			sum;

	count = 0;
	sum = 0;
	va_start(list, format);
	while (*format)
	{
		if (*format == '%' && ft_isin(*(format + 1), "cspdiuxX%"))
		{
			count = ft_format(list, *(format + 1));
			format += 2;
			sum = sum + count;
		}
		else
		{
			count = write(1, format++, 1);
			sum++;
		}
		if (count == -1)
			return (-1);
	}
	va_end(list);
	return (sum);
}
