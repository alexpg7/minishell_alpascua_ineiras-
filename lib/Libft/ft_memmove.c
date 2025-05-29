/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:27:28 by alpascua          #+#    #+#             */
/*   Updated: 2025/01/08 18:57:25 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*p1;
	unsigned char		*p2;
	size_t				i;

	i = 0;
	if (!dest || !src)
		return (NULL);
	p1 = (unsigned char *)src;
	p2 = (unsigned char *)dest;
	if (p1 < p2)
	{
		while (n-- > 0)
			p2[n] = p1[n];
	}
	else
	{
		while (i < n)
		{
			p2[i] = p1[i];
			i++;
		}
	}
	return (p2);
}
