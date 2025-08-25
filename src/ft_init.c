/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 20:05:21 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/25 19:09:16 by ineiras-         ###   ########.fr       */
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
	vars->pip = NULL;
	//vars->command = NULL;
	vars->ts = ft_lstnew_lst(NULL, NULL);
	if (!vars->ts)
		ft_exit(NULL, 2, vars);
	aux = ft_strjoin("?=0", "");
	if (!aux)
		ft_exit(NULL, 2, vars);
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

	i = 0;
	vars->input = NULL;
	aux = ft_strjoin("\"=\"", ""); //empty variable at the start
	if (!aux)
		ft_exit(NULL, 2, vars);
	env = ft_lstnew(aux);
	if (!env)
		ft_exit(NULL, 2, vars);
	while (envp[i])
	{
		aux = ft_strjoin(envp[i], "");
		if (!aux)
			ft_exit(NULL, 2, vars);
		new = ft_lstnew(aux);
		if (!new)
			ft_lstclear(&env, &free);
		ft_lstadd_back(&env, new);
		i++;
	}
	ft_init2(vars, env);
}
