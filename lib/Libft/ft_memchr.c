/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:12:54 by alpascua          #+#    #+#             */
/*   Updated: 2025/01/08 19:40:44 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*dest;

	if (!s)
		return (NULL);
	dest = (const char *)s;
	while (n >= 1)
	{
		if (*dest == (unsigned char)c)
			return ((void *)dest);
		dest++;
		n--;
	}
	return (NULL);
}
