/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitmini2_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 14:56:32 by alpascua          #+#    #+#             */
/*   Updated: 2025/09/10 18:42:33 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/minishell.h"

int	ft_isop(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int	ft_isquote(char c)
{
	if (c == '\"' || c == '\'')
		return (1);
	return (0);
}

int	ft_checkop(char *str, int *i)
{
	if (ft_isop(str[*i]))
	{
		if (str[*i] == '>' || str[*i] == '<')
		{
			if (str[*i] == str[*i + 1])
				*i = *i + 1;
		}
		*i = *i + 1;
		return (1);
	}
	return (0);
}
