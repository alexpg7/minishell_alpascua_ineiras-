/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 14:08:03 by alpascua          #+#    #+#             */
/*   Updated: 2025/01/12 12:49:35 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	ft_cont(char const *s1, char const *set, int *cont, int start)
{
	int	i;

	i = 0;
	if (start == -1)
		i = ft_strlen(s1) - 1;
	while (s1[i] && i >= 0)
	{
		if (!ft_strchr(set, s1[i]))
			break ;
		*cont = *cont + 1;
		i = i + start;
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		cont1;
	int		cont2;
	char	*str;
	size_t	size;

	if (!s1 || !set)
		return (NULL);
	cont1 = 0;
	cont2 = 0;
	ft_cont(s1, set, &cont1, 1);
	ft_cont(s1, set, &cont2, -1);
	if (ft_strlen(s1) < (size_t)(cont1 + cont2))
	{
		cont1 = ft_strlen(s1);
		cont2 = 0;
	}
	size = ft_strlen(s1) + 1 - cont1 - cont2;
	str = (char *)malloc(sizeof(char) * (size));
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s1[cont1], size);
	return (str);
}
