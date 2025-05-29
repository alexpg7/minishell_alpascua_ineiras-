/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:43:48 by alpascua          #+#    #+#             */
/*   Updated: 2025/01/12 14:22:34 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_search(const char *s1, const char *s2, size_t len)
{
	int		total;
	size_t	i;

	total = ft_strlen(s2);
	i = 0;
	while (total > 0 && i < len)
	{
		if (s1[i] != s2[i])
			return (0);
		total--;
		i++;
	}
	if (i >= len && total != 0)
		return (0);
	return (1);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (!big || !little)
		return (NULL);
	if (ft_strlen(little) == 0)
		return ((char *)big);
	i = 0;
	while (i < len && big[i])
	{
		if (big[i] == little[0])
		{
			if (ft_search(&big[i], little, len - i) == 1)
				return ((char *)(&big[i]));
		}
		i++;
	}
	return (NULL);
}
