/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitmini.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:05:29 by alpascua          #+#    #+#             */
/*   Updated: 2025/06/02 13:05:30 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../Libft/libft.h"
#include <stdio.h>

static int	ft_words(char const *s, char sep)
{
	int		i;
	int		cont;
	char	c;

	i = 0;
	cont = 0;
	while (s[i])
	{
		while (s[i] == sep)
			i++;
		if (s[i])
			cont++;
		while (s[i] && s[i] != sep)
		{
			if (s[i] == '\"' || s[i] == '\'')
			{
				c = s[i];
				i++;
				while (s[i] != c)
					i++;
			}
			i++;
		}
	}
	return (cont);
}

static int	ft_strlen2(const char *s, char com)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (s[i] == com)
			return (i + 1);
		i++;
	}
	return (i);
}

static int	ft_calclen(const char *s, char c)
{
	char	com;

	if (*s == '\'' || *s == '\"')
	{
		com = *s;
		return (ft_strlen2(s, com));
	}
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

char	**ft_splitmini(char const *s, char c)
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
/*int	main(int narg, char **argv)
{
	char **sp;
	int	i = 0;

	if (narg != 2)
		return (0);
	sp = ft_splitmini(argv[1], ' ');
	while (sp[i])
	{
		printf("%s\n", sp[i]);
		i++;
	}
	printf("%s\n", sp[i]);
	return (0);
}*/
