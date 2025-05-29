/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:36:40 by alpascua          #+#    #+#             */
/*   Updated: 2025/01/29 12:35:41 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		len;

	i = 0;
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ptr)
		return (NULL);
	if (s1)
	{
		while (s1[i])
		{
			ptr[i] = s1[i];
			i++;
		}
	}
	len = i;
	i = 0;
	while (s2[i])
	{
		ptr[len + i] = s2[i];
		i++;
	}
	ptr[i + len] = '\0';
	return (ptr);
}
