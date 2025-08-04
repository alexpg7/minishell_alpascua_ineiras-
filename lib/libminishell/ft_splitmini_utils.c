/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitmini_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:24:15 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/04 16:24:18 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../src/minishell.h"
#include <stdio.h>

void	ft_jumpcom(char const **s, char sep)
{
	char	c;

	while (**s && **s != sep)
	{
		if (**s == '\"' || **s == '\'')
		{
			c = **s;
			*s = *s + 1;
			while (**s != c)
				*s = *s + 1;
			*s = *s + 1;
		}
	}
}

int	ft_special(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

void	ft_nextword(const char **s, char sep)
{
	if (**s == '\'' || **s == '\"')
	{
		ft_jumpcom(s, sep);
		return ;
	}
	else if (**s == '|')
	{
		*s = *s + 1;
		return ;
	}
	else if (**s == '>')
	{
		*s = *s + 1 + (*(*s + 1) == '>');
		return ;
	}
	else if (**s == '<')
	{
		*s = *s + 1 + (*(*s + 1) == '<');
		return ;
	}
	while (**s != ' ' && !ft_special(**s) && **s)
		*s = *s + 1;
}
