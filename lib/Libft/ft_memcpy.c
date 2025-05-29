/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:14:22 by alpascua          #+#    #+#             */
/*   Updated: 2025/01/08 19:37:27 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*p1;
	const unsigned char	*p2;
	size_t				i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	p1 = (unsigned char *)dest;
	p2 = (unsigned char *)src;
	while (i < n)
	{
		p1[i] = p2[i];
		i++;
	}
	return (dest);
}
