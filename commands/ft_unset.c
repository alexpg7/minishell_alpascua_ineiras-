/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:27:24 by ineiras-          #+#    #+#             */
/*   Updated: 2025/08/30 17:03:51 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

int	ft_strisalnum2(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum2(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	ft_delete_env2(char *var, t_vars *vars)
{
	t_list	*prev;
	t_list	*env;
	int		len1;
	int		len2;

	prev = vars->env;
	env = vars->env->next;
	while (env)
	{
		len1 = ft_varlen2(var);
		len2 = ft_varlen2(env->content);
		len1 = len1 * (len1 > len2) + len2 * (len1 <= len2);
		if (ft_strncmp(var, env->content, len1) == 0)
		{
			prev->next = env->next;
			ft_lstdelone(env, &free);
			return ;
		}
		prev = prev->next;
		env = env->next;
	}
}

static void	ft_delete_env(char *var, t_vars *vars)
{
	if (!ft_strisalnum2(var))
	{
		ft_putstr_fd("unset: ", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd(": invalid parameter name.\n", 2);
		return ;
	}
	ft_delete_env2(var, vars);
}

void	ft_unset(char **args, t_vars *vars)
{
	while (*args)
	{
		ft_delete_env(*args, vars);
		args++;
	}
}
