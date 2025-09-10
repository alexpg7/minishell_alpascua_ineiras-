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

void	ft_exit2(char *input, int ret, t_vars *vars)
{
	int	i;

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
	if (vars->input)
		ft_freeinput(&vars->input, vars->np, vars);
	if (vars->pip)
		ft_freepip(vars->pip, vars->np, vars->np + 1);
	exit(ret);
}

int	ft_checknum(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi255(char *str)
{
	int	num;

	num = ft_atoi(str);
	num = num % 255;
	return (num);
}

void	ft_exit(char *input, char **args, int ret, t_vars *vars)
{
	int	num;

	if (args == NULL)
		ft_exit2(input, ret, vars);
	else if (args[0] != NULL)
	{
		if (args[1] == NULL)
		{
			if (ft_checknum(args[0]) == 1)
			{
				num = ft_atoi255(args[0]);
				ft_exit2(input, num, vars);
			}
			else
			{
				ft_putstr_fd("exit: not a valid argument.\n", 2);
				ft_exit2(input, 2, vars);
			}
		}
		else
			ft_putstr_fd("exit: too many arguments.\n", 2);
	}
	else
		ft_exit2(input, ret, vars);
}
