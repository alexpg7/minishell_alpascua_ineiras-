/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lenvars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:02:42 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/30 17:02:45 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/minishell.h"

void	ft_nextvar(char *comm, int *i)
{
	*i = *i + 1;
	while (comm[*i])
	{
		if (comm[*i] == '$')
			break ;
		*i = *i + 1;
	}
	*i = *i - 1;
}

int	ft_strcmpvar(char *var, char *name, int len)
{
	int	i;

	i = 0;
	while (var[i] == name[i] && var[i] && name[i] && i < len)
		i++;
	if (var[i] == '=' && i == len)
		return (0);
	return (var[i] - name[i]);
}

int	ft_isvar_clean(char *comm, int len, t_vars *vars)
{
	t_list	*env;
	char	*str;

	env = vars->env;
	if (!ft_isalpha(comm[0]) && comm[0] != '_' && comm[0] != '?')
		return (-1);
	while (env)
	{
		if (ft_strcmpvar(env->content, comm, len) == 0)
		{
			str = ft_strchr(env->content, '=');
			if (str)
				return (ft_strlen(ft_strchr(env->content, '=') + 1));
			else
				return (0);
		}
		env = env->next;
	}
	return (0);
}

int	ft_varlen_clean(char *comm, t_vars *vars)
{
	int	i;

	i = 0;
	if (comm[0] == '?')
		return (ft_isvar_clean(comm, 1, vars) - 1);
	while (comm[i])
	{
		if (!ft_isalnum2(comm[i]))
			break ;
		i++;
	}
	return (ft_isvar_clean(comm, i, vars) - i);
}

int	ft_lenvars_clean(char *comm, t_vars *vars)
{
	int		i;
	int		len;
	char	c;

	i = 0;
	len = 0;
	c = '0';
	while (comm[i])
	{
		if (comm[i] == '\'' && c == '0' && comm[i - (i != 0)] != '\\')
			ft_nextword2(comm, &i);
		else if (comm[i] == '$' && (ft_isalpha(comm[i + 1]) || comm[i + 1] == '_'))
		{
			len += ft_varlen_clean(&comm[i + 1], vars) - 1;
			ft_nextvar(comm, &i);
		}
		else if (comm[i])
		{
			if (comm[i] == '\"' && comm[i - (i != 0)] != '\\')
				c = '\"' * (c == '0') + '0' * (c == '\"');
			i++;
		}
	}
	return (len);
}
