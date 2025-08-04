/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:48:21 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/04 16:48:24 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../src/minishell.h"

char	ft_isspecial(char c)
{
	if (c == 't')
		return ('\t');
	else if (c == 'n')
		return ('\n');
	else if (c == 'v')
		return ('\v');
	else if (c == 'f')
		return ('\f');
	else if (c == 'r')
		return ('\r');
	return ('\0');
}

static int	ft_countspecial(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			if (ft_isspecial(str[i + 1]))
				count++;
		}
		i++;
	}
	return (count);
}

void	ft_appendchar(char *ptr, char **str, int i)
{
	if (**str == '\\' && ft_isspecial(*(*str + 1)))
	{
		ptr[i] = ft_isspecial(*(*str + 1));
		*str = *str + 1;
	}
	else
		ptr[i] = **str;
}

char	*ft_remove(char *str, int count)
{
	char	*ptr;
	int		i;
	char	*start;
	char	c;

	ptr = (char *)malloc(sizeof(char) * (ft_strlen(str)- 1 - count));
	if (!ptr)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	c = str[0];
	start = str;
	str++;
	while (*str && *str != c)
	{
		ft_appendchar(ptr, &str, i);
		i++;
		str++;
	}
	free(start);
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_removequotes(char *str)
{
	int	count;

	if (str[0] != '\"' && str[0] != '\'')
		return (str);
	count = ft_countspecial(str);
	return (ft_remove(str, count));
}
