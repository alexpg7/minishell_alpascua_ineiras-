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

char	*ft_searchvar(char *comm, int len, t_vars *vars)
{
	t_list	*env;
	char	*str;

	env = vars->env;
	while (env)
	{
		if (ft_strcmpvar(env->content, comm, len) == 0)
		{
			str = ft_strchr(env->content, '=');
			if (str)
				return (str + 1);
			else
				return (ft_strchr(env->content, '\0'));
		}
		env = env->next;
	}
	return (NULL);
}

static void	ft_countlen(char *src, int *i, int *len)
{
	*len = 0;
	while (src[*i + 1 + *len])
	{
		if (!ft_isalpha(src[*i + 1]) && src[*i + 1] != '_')
			break ;
		else if (!ft_isalnum2(src[*i + 1 + *len]))
			break ;
		*len = *len + 1;
	}
}

void	ft_copyvar(char **dest, char *src, int *i, t_vars *vars)
{
	int	len;
	int	varlen;

	if (src[*i + 1] == '?')
		len = 1;
	else
		ft_countlen(src, i, &len);
	varlen = ft_isvar_clean(&src[*i + 1], len, vars);
	if (varlen > 0)
		ft_strlcpy(*dest, ft_searchvar(&src[*i + 1], len, vars), varlen + 1);
	else if (varlen < 0)
		ft_strlcpy(*dest, "$", 2);
	else if (varlen == 0)
		ft_strlcpy(*dest, "", 1);
	*dest = *dest + varlen + 0 * (varlen == 0) + 2 * (varlen < 0);
	*i = *i + len + 1;
}
