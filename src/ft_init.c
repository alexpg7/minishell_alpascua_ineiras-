/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 20:05:21 by alpascua          #+#    #+#             */
/*   Updated: 2025/07/30 20:05:22 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init2(t_vars *vars, t_list *env)
{
	t_list	*new;
	char	*aux;

	vars->envp = NULL;
	vars->env = env;
	vars->exit_status = 0;
	vars->np = 0;
	vars->command = NULL;
	vars->ts = ft_lstnew_lst(NULL, NULL);
	if (!vars->ts)
		ft_exit(NULL, 1, vars);
	aux = ft_strjoin("?=0", "");
	if (!aux)
		ft_exit(NULL, 1, vars);
	new = ft_lstnew(aux);
	if (!new)
		ft_lstclear(&vars->env, &free);
	ft_lstadd_back(&vars->env, new);
}

void	ft_init(t_vars *vars, char **envp)
{
	t_list	*env;
	t_list	*new;
	char	*aux;
	int		i;

	i = 1;
	aux = ft_strjoin(envp[0], "");
	if (!aux)
		ft_exit(NULL, 1, vars);
	env = ft_lstnew(aux);
	if (!env)
		ft_exit(NULL, 1, vars);
	while (envp[i])
	{
		aux = ft_strjoin(envp[i], "");
		if (!aux)
			ft_exit(NULL, 1, vars);
		new = ft_lstnew(aux);
		if (!new)
			ft_lstclear(&env, &free);
		ft_lstadd_back(&env, new);
		i++;
	}
	ft_init2(vars, env);
}
