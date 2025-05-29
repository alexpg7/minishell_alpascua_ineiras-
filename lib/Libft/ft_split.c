/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 13:03:24 by alpascua          #+#    #+#             */
/*   Updated: 2025/01/29 12:31:08 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

static int	ft_words(char const *s, char sep)
{
	int	i;
	int	cont;

	i = 0;
	cont = 0;
	while (s[i])
	{
		while (s[i] == sep)
			i++;
		if (s[i])
			cont++;
		while (s[i] && s[i] != sep)
			i++;
	}
	return (cont);
}

static int	ft_calclen(const char *s, char c)
{
	if (!ft_strchr(s, c))
		return (ft_strlen(s));
	return (ft_strchr(s, c) - s);
}

static void	ft_free(char **ptr, int i)
{
	int	cont;

	cont = 0;
	while (cont < i)
	{
		free(ptr[cont]);
		cont++;
	}
	free(ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		words;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	words = ft_words(s, c);
	ptr = (char **)malloc((words + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			ptr[i] = ft_substr(s, 0, ft_calclen(s, c));
			if (!ptr[i])
				ft_free(ptr, i);
			s = s + ft_calclen(s, c) - 1;
			i++;
		}
		s++;
	}
	ptr[i] = NULL;
	return (ptr);
}
