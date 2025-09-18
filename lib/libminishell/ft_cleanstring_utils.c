/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanstring_utils.c                             :+:      :+:    :+:   */
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

char	*ft_searchvar(char *comm, int len, t_vars *vars)
{
	t_list	*env;

	env = vars->env;
	while (env)
	{
		if (ft_strcmpvar(env->content, comm, len) == 0)
			return (ft_strchr(env->content, '=') + 1);
		env = env->next;
	}
	return (NULL);
}

void	ft_copyvar(char **dest, char *src, int *i, t_vars *vars)
{
	int	len;
	int	varlen;

	if (src[*i + 1] == '?')
		len = 1;
	else
	{
		len = 0;
		while (src[*i + 1 + len])
		{
			if (!ft_isalpha(src[*i + 1]) && src[*i + 1] != '_')
				break ;
			else if (!ft_isalnum2(src[*i + 1 + len]))
				break ;
			len++;
		}
	}
	varlen = ft_isvar_clean(&src[*i + 1], len, vars);
	if (varlen > 0)
		ft_strlcpy(*dest, ft_searchvar(&src[*i + 1], len, vars), varlen + 1);
	else if (varlen < 0)
		ft_strlcpy(*dest, "$", 2);
	else if (varlen == 0)
		ft_strlcpy(*dest, "\0", 1);
	*dest = *dest + varlen + (varlen == 0) + (varlen < 0) ;
	*i = *i + len + 1;
}
