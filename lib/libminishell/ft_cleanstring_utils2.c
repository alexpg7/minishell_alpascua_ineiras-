/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanstring_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:05:05 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/30 17:05:07 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/minishell.h"

static void	ft_countspecial2(char *comm, int *count, int *i, char *c)
{
	if (ft_isquote(comm[*i]) && comm[*i - (*i != 0)] != '\\')
	{
		if (*c == '0')
			*c = comm[*i];
		else if (*c == comm[*i])
			*c = '0';
		*i = *i + 1;
		return ;
	}
	if (ft_isspecial2(&comm[*i]) && *c != '0')
	{
		count++;
		*i = *i + 1;
		if (comm[*i])
			*i = *i + 1;
	}
	else
		*i = *i + 1;
}

int	ft_isspecial2(char *c)
{
	if (c[1] == '\0')
		return (0);
	if (*c == '\\')
	{
		if (c[1] == 'n')
			return ('\n');
		else if (c[1] == 't')
			return ('\t');
		else if (c[1] == 'r')
			return ('\r');
		else if (c[1] == 'f')
			return ('\f');
		else if (c[1] == 'v')
			return ('\v');
		else if (c[1] == '\"')
			return ('\"');
		else if (c[1] == '\'')
			return ('\'');
	}
	return (0);
}

int	ft_countspecial(char *comm)
{
	int		i;
	int		count;
	char	c;

	i = 0;
	count = 0;
	c = '0';
	while (comm[i])
		ft_countspecial2(comm, &count, &i, &c);
	return (count);
}

int	ft_countquotes(char *comm)
{
	int		i;
	int		count;
	char	c;

	i = 0;
	count = 0;
	while (comm[i])
	{
		if (ft_isquote(comm[i]) && comm[i - (i != 0)] != '\\')
		{
			count++;
			c = comm[i];
			i++;
			while (comm[i] && !(comm[i] == c && comm[i - (i != 0)] != '\\'))
				i++;
		}
		if (comm[i])
			i++;
	}
	return (count);
}
