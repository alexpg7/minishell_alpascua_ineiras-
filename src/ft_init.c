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
	vars->here = ft_strdup(".here_doc_000.tmp");
	if (!vars->here)
		ft_exit(NULL, NULL, 1, vars);
	vars->ts = ft_lstnew_lst(NULL, NULL);
	if (!vars->ts)
		ft_exit(NULL, NULL, 1, vars);
	aux = ft_strjoin("?=0", "");
	if (!aux)
		ft_exit(NULL, NULL, 1, vars);
	new = ft_lstnew(aux);
	if (!new)
		ft_lstclear(&vars->env, &free);
	ft_lstadd_back(&vars->env, new);
	ft_init3(vars);
}

char	*ft_shlvl(char *envp, t_vars *vars)
{
	int		num;
	char	*aux;
	char	*ret;

	num = ft_atoi(ft_strchr(envp, '=') + 1);
	aux = ft_itoa(num + 1);
	if (!aux)
		ft_exit(NULL, NULL, 1, vars);
	ret = ft_strjoin("SHLVL=", aux);
	free(aux);
	if (!ret)
		ft_exit(NULL, NULL, 1, vars);
	return (ret);
}

void	ft_init1(t_list **env, t_vars *vars, char **aux)
{
	vars->input = NULL;
	vars->prompt = NULL;
	*aux = ft_strjoin("\"=\0", "");
	if (!(*aux))
		ft_exit(NULL, NULL, 1, vars);
	*env = ft_lstnew(*aux);
	if (!(*env))
		ft_exit(NULL, NULL, 1, vars);
}

void	ft_init(t_vars *vars, char **envp)
{
	t_list	*env;
	t_list	*new;
	char	*aux;
	int		i;

	i = 0;
	ft_init1(&env, vars, &aux);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL", 5) == 0)
			aux = ft_shlvl(envp[i], vars);
		else
			aux = ft_strjoin(envp[i], "");
		if (!aux)
			ft_exit(NULL, NULL, 1, vars);
		new = ft_lstnew(aux);
		if (!new)
			ft_lstclear(&env, &free);
		ft_lstadd_back(&env, new);
		i++;
	}
	ft_init2(vars, env);
}
