/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:23:51 by ineiras-          #+#    #+#             */
/*   Updated: 2025/08/30 17:26:24 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	ft_freeall(t_vars *vars)
{
	if (vars->prompt)
		free(vars->prompt);
}

void	ft_exit(char *input, int ret, t_vars *vars)
{
	int	i;

	//if narg == 1 or 2, do, else error.
	//return as exit status the first argument, if NaN exit=2
	if (input)
		free(input);
	rl_clear_history();
	ft_freeall(vars);
	if (vars->envp)
		ft_freestrarr(&vars->envp, 1);
	ft_lstclear_lst(&vars->ts);
	ft_lstclear(&vars->env, &free);
	i = 0;
	while (++i < vars->np)
		unlink(ft_sufix(vars->here, i));
	free(vars->here);
	if (ret == 2)
	{
		ft_putstr_fd("malloc error\n", 2);//remove from all files
		exit(1);
	}
	if (vars->input)
		ft_freeinput(&vars->input, vars->np, vars);
	if (vars->pip)
		ft_freepip(vars->pip, vars->np, vars->np + 1);
	exit(ret);
}
