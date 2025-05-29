/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:56:34 by alpascua          #+#    #+#             */
/*   Updated: 2025/01/08 19:41:29 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*dest;

	if (!s)
		return (NULL);
	dest = (char *)s;
	while (*dest)
	{
		if (*dest == (unsigned char)c)
			return (dest);
		dest++;
	}
	if (c == '\0')
		return ((char *)dest);
	return (NULL);
}
