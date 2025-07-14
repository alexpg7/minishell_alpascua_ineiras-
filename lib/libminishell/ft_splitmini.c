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
#include "../../src/minishell.h"
#include <stdio.h>

static int	ft_words(char const *s, char sep)
{
	int	cont;

	cont = 0;
	while (*s)
	{
		while (*s == sep)
			s++;
		if (*s != '\0' && *s != sep)
			cont++;
		ft_nextword(&s, sep);
	}
	return (cont);
}

static int	ft_wordlen(char const *s, char sep)
{
	const char	*aux;

	aux = s;
	ft_nextword(&aux, sep);
	return (aux - s);
}

void	ft_assignvars(char **ptr, int i, t_vars *vars)
{
	if (ft_strlen(ptr[i]) == 1)
	{
		if (ptr[i][0] == '|')
			vars->np = vars->np + 1;
	}
}

char	**ft_splitmini(char const *s, char c, t_vars *vars)
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
	while (*s && words > 0)
	{
		while (*s == c)
			s++;
		ptr[i] = ft_substr(s, 0, ft_wordlen(s, c));
		if (!ptr[i])
			return (ft_free(ptr, i));
		ft_nextword((const char **)&s, c);
		ft_assignvars(ptr, i, vars);
		words--;
		i++;
	}
	ptr[i] = NULL;
	return (ptr); //NO PASA LA NORMA
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
		free(sp[i - 1]);
	}
	printf("%s\n", sp[i]);
	free(sp);
	return (0);
}*/
