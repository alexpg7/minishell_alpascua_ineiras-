/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:37:25 by alpascua          #+#    #+#             */
/*   Updated: 2025/09/19 16:37:27 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_initexport(char *str, t_vars *vars)
{
	ft_export(vars, &str, 1);
}

void	ft_initpwd(char *str, t_vars *vars)
{
	char	*new;
	char	*total;

	new = ft_new_pwd();
	if (!new)
		ft_exit(NULL, NULL, 1, vars);
	total = ft_strjoin(str, new);
	free(new);
	if (!total)
		ft_exit(NULL, NULL, 1, vars);
	ft_export(vars, &total, 1);
	free(total);
}

void	ft_init3(t_vars *vars)
{
	if (!ft_searchvar("PWD", 5, vars))
		ft_initpwd("PWD=", vars);
	if (!ft_searchvar("SHLVL", 5, vars))
		ft_initexport("SHLVL=1", vars);
}
