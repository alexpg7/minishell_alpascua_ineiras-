/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:28:03 by ineiras-          #+#    #+#             */
/*   Updated: 2025/08/06 15:52:37 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

static int	ft_varlen2(char *str)
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

	env = vars->env;
	while (env)
	{
		if (ft_strncmp(str, env->content, ft_varlen2(str) + 1) == 0)
		{
			free(env->content);
			env->content = new_var(vars, str);
			if (!env->content)
				ft_exit(NULL, 1, vars);
		}
		env = env->next;
	}
}

int	ft_inenv(char *str, t_vars *vars)
{
	t_list	*env;

	env = vars->env;
	while (env)
	{
		if (ft_strncmp(str, env->content, ft_varlen2(str) + 1) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

void	ft_export(t_vars *vars, char **arg, int mode)
{
	if (!(*arg))
	{
		ft_env(vars);
		return ;
	}
	while (arg && *arg && ft_strchr(*arg, '='))
	{
		if (ft_strisalnum2(*arg) == 0 && **arg != '?')
		{
			arg++;
			continue ;
		}
		if (ft_inenv(*arg, vars))
			ft_subsenv(*arg, vars);
		else
			ft_lstadd_back(&vars->env, ft_lstnew(new_var(vars, *arg)));
		if (mode == 1)
			break ;
		arg++;
	}
}

char	*new_var(t_vars *vars, char *arg)
{
	char	*str;
	char	*str_ae;
	char	*str_en;

	if (!arg)
		return (NULL);
	str = ft_strdup_eq(arg);
	if (!str)
		ft_exit(NULL, 2, vars);
	str_ae = ft_strdup(ft_strchr(arg, '=') + 1);
	if (!str_ae)
		ft_exit(NULL, 2, vars);
	str_ae = ft_searchdollar(str_ae, vars);
	if (!str_ae)
		ft_exit(NULL, 2, vars);
	str_ae = ft_removequotes(str_ae);
	if (!str_ae)
		ft_exit(NULL, 2, vars);
	str_en = ft_strjoin(str, str_ae);
	if (!str_en)
		ft_exit(NULL, 2, vars);
	ft_free_both(str, str_ae);
	return (str_en);
}
