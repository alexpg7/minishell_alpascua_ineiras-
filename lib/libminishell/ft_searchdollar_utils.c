/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_searchdollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:25:29 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/04 16:25:32 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../src/minishell.h"

int	ft_varlen(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '?')
		return (1);
	if (!str)
		return (0);
	while (ft_isalnum2(str[i]))
		i++;
	return (i);
}

//mode 1 means start with '$', mode 0 not

int	ft_isvar(char *str, t_vars *vars, int mode)
{
	t_list	*env;
	int		len;

	env = vars->env;
	if (*str == '$' && *(str + 1) == '?')
		return (2);
	if (*str == '$' && ft_isalnum2(*(str + 1)))
	{
		while (env)
		{
			len = ft_varlen(env->content);
			if (ft_strncmp(env->content, str + mode, len) == 0)
				return (len + 1);
			env = env->next;
		}
	}
	return (0);
}

int	ft_countvars(char *str, t_vars *vars)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_isvar(&str[i], vars, 1))
			count++;
		i++;
	}
	return (count);
}
