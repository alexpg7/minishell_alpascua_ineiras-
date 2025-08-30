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
	}
	return (0);
}
