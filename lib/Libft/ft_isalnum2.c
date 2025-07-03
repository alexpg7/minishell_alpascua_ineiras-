/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 13:15:28 by alpascua          #+#    #+#             */
/*   Updated: 2024/12/20 14:45:09 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isalnum2(int c)
{
	int	num;
	int	up;
	int	low;
	int	space;

	num = (c >= '0' && c <= '9');
	up = (c >= 'A' && c <= 'Z');
	low = (c >= 'a' && c <= 'z');
	space = (c == '_');
	if (num || up || low || space)
		return (1);
	else
		return (0);
}
