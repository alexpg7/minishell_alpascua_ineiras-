/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:20:46 by alpascua          #+#    #+#             */
/*   Updated: 2024/12/22 17:32:35 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_digits(int n)
{
	int	i;

	i = 0;
	while (n / 10 != 0)
	{
		i++;
		n = n / 10;
	}
	return (i + 1);
}

static void	ft_writenum(char *str, unsigned int n, int size)
{
	str = str + size - 1;
	*str = '\0';
	str--;
	while (n / 10 != 0)
	{
		*str = n % 10 + '0';
		str--;
		n = n / 10;
	}
	*str = n % 10 + '0';
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		size;

	size = ft_digits(n) + 1 + (n < 0);
	ptr = (char *)malloc(sizeof(char) * size);
	if (!ptr)
		return (NULL);
	if (n < 0)
	{
		*ptr = '-';
		n = (unsigned int)(-n);
	}
	else
		n = (unsigned int)n;
	ft_writenum(ptr, n, size);
	return (ptr);
}
