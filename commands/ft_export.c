/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:28:03 by ineiras-          #+#    #+#             */
/*   Updated: 2025/08/30 18:04:23 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

int	ft_varlen2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

static void	ft_subsenv(char *str, t_vars *vars)
{
	t_list	*env;
	int		len1;
	int		len2;

	env = vars->env;
	while (env)
	{
		len1 = ft_varlen2(env->content);
		len2 = ft_varlen2(str);
		len1 = len1 * (len1 > len2) + len2 * (len1 <= len2);
		if (ft_strncmp(str, env->content, len1) == 0)
		{
			free(env->content);
			if (*str != '?')
				env->content = ft_strdup(str);
			else
				env->content = str;
		}
		env = env->next;
	}
}

int	ft_inenv(char *str, t_vars *vars)
{
	t_list	*env;
	int		len1;
	int		len2;

	env = vars->env;
	while (env)
	{
		len1 = ft_varlen2(env->content);
		len2 = ft_varlen2(str);
		len1 = len1 * (len1 > len2) + len2 * (len1 <= len2);
		if (ft_strncmp(str, env->content, len1) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

static void	exp_logic(t_vars *vars, char **arg, int mode)
{
	while (arg && *arg)
	{
		if (**arg != '?' && mode == 0)
			vars->exit_status = 0;
		if (ft_strisalnum2(*arg) == 1 || **arg == '?')
		{
			if (ft_strisalnum2(*arg) == 0 && **arg != '?')
			{
				ft_printerror(vars, *arg);
				arg++;
				continue ;
			}
			if (ft_inenv(*arg, vars))
				ft_subsenv(*arg, vars);
			else
				ft_lstadd_back(&vars->env, ft_lstnew(ft_strdup(*arg)));
			if (mode == 1)
				break ;
		}
		else
			ft_printerror(vars, *arg);
		arg++;
	}
}

void	ft_export(t_vars *vars, char **arg, int mode)
{
	if (!(*arg))
	{
		ft_env_export(vars);
		return ;
	}
	if (**arg != '?' && mode == 0)
		vars->exit_status = 0;
	exp_logic(vars, arg, mode);
}
