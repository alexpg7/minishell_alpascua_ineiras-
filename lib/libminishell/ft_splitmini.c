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
	int	i;
	int	cont;

	i = 0;
	cont = 0;
	while (s[i])
	{
		while (s[i] == sep)
			i++;
		if (s[i] != '\0' && s[i] != sep)
			cont++;
		ft_nextword(s, &i, sep);
	}
	return (cont);
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

static int	ft_wordlen(char const *s, char sep)
{
	int	i;

	i = 0;
	ft_nextword(s, &i, sep);
	return (i);
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
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	words = ft_words(s, c);
	ptr = (char **)malloc((words + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	while (s[j] && words > 0)
	{
		while (s[j] == c)
			j++;
		ptr[i] = ft_substr(s, j, ft_wordlen(&s[j], c));
		if (!ptr[i])
			ft_free(ptr, i);
		ft_nextword(s, &j, c);
		ft_assignvars(ptr, i, vars);
		words--;
		i++;
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
		free(sp[i - 1]);
	}
	printf("%s\n", sp[i]);
	free(sp);
	return (0);
}*/
