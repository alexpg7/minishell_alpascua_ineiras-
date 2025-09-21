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

void	ft_exit2(char *str, char *ptr, int ret, t_vars *vars)
{
	int	i;

	if (str)
		ft_putstr_fd(str, 2);
	rl_clear_history();
	if (vars->prompt)
		free(vars->prompt);
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
	if (ptr)
		free(ptr);
	if (vars->pip)
		ft_freepip(vars->pip, vars->np, vars->np + 1);
	exit(ret);
}
/*	if (ft_strlen(str + i) > 10)
		return (0);
	if (ft_atoi(str + i) * ft_atoi(str + i - (flag == 1)) < 0)
		return (0);*/

int	ft_checknum(char *str)
{
	int		i;
	int		sign;
	char	*orig;

	i = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	orig = str + i;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (ft_strlen(str + i) > 10)
		return (0);
	if ((long)ft_atoi(orig) * (long)sign < 0)
		return (0);
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
	num = num % 256;
	return (num);
}

void	ft_exit(char *ptr, char **args, int ret, t_vars *vars)
{
	int	num;

	if (args == NULL)
		ft_exit2(NULL, ptr, ret, vars);
	else if (args[0] != NULL)
	{
		if (args[1] == NULL)
		{
			if (ft_checknum(args[0]) == 1)
			{
				num = ft_atoi255(args[0]);
				ft_exit2(NULL, ptr, num, vars);
			}
			else
				ft_exit2("exit: numeric argument required.\n", ptr, 2, vars);
		}
		else
		{
			ft_putstr_fd("exit: too many arguments.\n", 2);
			vars->exit_status = 1;
		}
	}
	else
		ft_exit2(NULL, ptr, ret, vars);
}

void	ft_exitbuiltin(char *ptr, char **args, int ret, t_vars *vars)
{
	ft_putstr_fd("exit\n", 2);
	ft_exit(ptr, args, ret, vars);
}
