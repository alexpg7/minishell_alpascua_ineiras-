/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:56:34 by alpascua          #+#    #+#             */
/*   Updated: 2025/07/30 16:39:29 by ineiras-         ###   ########.fr       */
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
