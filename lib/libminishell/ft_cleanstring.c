/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanstring.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 13:58:38 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/30 13:58:42 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/minishell.h"

char	ft_unquoted(char **dest, char *src, int *i, t_vars *vars)
{
	if (ft_isquote(src[*i]) && src[*i - (*i != 0)] != '\\')
	{
		*i = *i + 1;
		return (src[*i - 1]);
	}
	else if (src[*i] == '$')
		ft_copyvar(dest, src, i, vars);
	else
	{
		**dest = src[*i];
		*i = *i + 1;
		*dest = *dest + 1;
	}
	return ('0');
}

char	ft_quoted1(char **dest, char *src, int *i)
{
	if (src[*i] == '\'' && src[*i - (*i != 0)] != '\\')
	{
		*i = *i + 1;
		return ('0');
	}
	else if (ft_isspecial2(&src[*i]))
	{
		**dest = ft_isspecial2(&src[*i]);
		*dest = *dest + 1;
		*i = *i + 2;
	}
	else
	{
		**dest = src[*i];
		*i = *i + 1;
		*dest = *dest + 1;
	}
	return ('\'');
}

char	ft_quoted2(char **dest, char *src, int *i, t_vars *vars)
{
	if (src[*i] == '\"' && src[*i - (*i != 0)] != '\\')
	{
		*i = *i + 1;
		return ('0');
	}
	else if (ft_isspecial2(&src[*i]))
	{
		**dest = ft_isspecial2(&src[*i]);
		*dest = *dest + 1;
		*i = *i + 2;
	}
	else if (src[*i] == '$')
		ft_copyvar(dest, src, i, vars);
	else
	{
		**dest = src[*i];
		*i = *i + 1;
		*dest = *dest + 1;
	}
	return ('\"');
}

void	ft_copyclean(char *dest, char *src, t_vars *vars)
{
	int		i;
	char	c;

	i = 0;
	c = '0';
	while (src[i])
	{
		if (c == '0')
		{
			c = ft_unquoted(&dest, src, &i, vars);
			continue ;
		}
		else if (c == '\'')
		{
			c = ft_quoted1(&dest, src, &i);
			continue ;
		}
		else if (c == '\"')
		{
			c = ft_quoted2(&dest, src, &i, vars);
			continue ;
		}
	}
	*dest = '\0';
}

char	*ft_cleanstring(char *comm, char token, t_vars *vars)
{
	int		lendiff;
	char	*ptr;
	char	*dupcomm;

	if (token != 'w' && token != 'c')
	{
		dupcomm = ft_strdup(comm);
		if (!dupcomm)
			ft_exit(NULL, NULL, 1, vars);
		return (dupcomm);
	}
	lendiff = -2 * ft_countquotes(comm);
	lendiff = ft_lenvars_clean(comm, vars);
	lendiff += -ft_countspecial(comm);
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(comm) + lendiff + 1));
	if (!ptr)
		ft_exit(NULL, NULL, 1, vars);
	ft_copyclean(ptr, comm, vars);
	return (ptr);
}
