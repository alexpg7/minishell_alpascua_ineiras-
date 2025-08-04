/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:27:24 by ineiras-          #+#    #+#             */
/*   Updated: 2025/08/04 18:27:46 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

int	ft_strisalnum2(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum2(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	ft_delete_env2(char *var, int len, t_vars *vars)
{
	t_list	*prev;
	t_list	*env;

	prev = vars->env;
	env = vars->env->next;
	while (env)
	{
		if (ft_strncmp(var, env->content, len) == 0)
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
	int		len;
	t_list	*env;

	len = ft_strlen(var);
	if (!ft_strisalnum2(var))
	{
		ft_putstr_fd("unset: ", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd(": invalid parameter name.\n", 2);
		return ;
	}
	env = vars->env;
	if (ft_strncmp(env->content, var, len) == 0)
	{
		vars->env = env->next;
		ft_lstdelone(env, &free);
		return ;
	}
	ft_delete_env2(var, len, vars);
}

void	ft_unset(char **args, t_vars *vars)
{
	while (*args)
	{
		ft_delete_env(*args, vars);
		args++;
	}
}
