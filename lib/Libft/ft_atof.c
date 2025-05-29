/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:30:54 by alpascua          #+#    #+#             */
/*   Updated: 2025/05/08 17:38:21 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

float	ft_pow(float a, float b)
{
	float	nb;
	int		sign;

	nb = 1;
	sign = 1;
	if (b < 0)
	{
		sign = -1;
		b = -b;
	}
	if (b == 0)
		return (1);
	while (b > 0)
	{
		nb = nb * a;
		b--;
	}
	if (sign == -1)
		return (1 / nb);
	return (nb);
}

double	ft_atof(const char *str)
{
	double	int_part;
	double	dec_part;
	double	sign;
	int		i;

	int_part = 0.0;
	dec_part = 0.0;
	sign = 1.0;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1.0;
	while (ft_isdigit(*str))
		int_part = int_part * 10 + (*str++ - '0');
	i = -1;
	if (*str == '.' && *str++)
	{
		while (ft_isdigit(*str))
			dec_part += (ft_pow(10, i--) * (*str++ - '0'));
	}
	return (sign * (int_part + dec_part));
}
