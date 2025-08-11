/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:23:51 by ineiras-          #+#    #+#             */
/*   Updated: 2025/08/04 18:24:11 by ineiras-         ###   ########.fr       */
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
	if (input)
		free(input);
	rl_clear_history();
	ft_freeall(vars);
	if (vars->np >= 1)
	{
		free(vars->pid);
		ft_freepip(vars->pip, vars->np, vars->np + 1);
	}
	if (vars->envp)
		ft_freestrarr(&vars->envp, 1);
	ft_lstclear_lst(&vars->ts);
	//if (vars->command)
	//	ft_freecommand(vars->command);
	ft_lstclear(&vars->env, &free);
	unlink(".here_doc.tmp");
	if (ret == 2)
	{
		ft_putstr_fd("malloc error\n", 2);
		exit(1);
	}
	exit(ret);
}
