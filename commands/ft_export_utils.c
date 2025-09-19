/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 18:02:36 by ineiras-          #+#    #+#             */
/*   Updated: 2025/09/18 20:02:45 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	ft_printerror(t_vars *vars, char *arg)
{
	ft_putstr_fd("export: not valid in this context: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putchar_fd('\n', 2);
	vars->exit_status = 1;
}

void	ft_set_index(t_vars *vars)
{
	t_list	*lst;

	lst = vars->env->next;
	while (lst)
	{
		lst->index = -1;
		lst = lst->next;
	}
}

int	ft_lst_counter(t_vars *vars)
{
	int		i;
	t_list	*lst;

	i = 0;
	lst = vars->env->next;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_list	*ft_setmax(t_list *lst)
{
	t_list	*max;

	max = lst;
	while (lst)
	{
		if ((lst->index == -1)
			&& (ft_strcmp((char *)max->content, (char *)lst->content) < 0))
			max = lst;
		lst = lst->next;
	}
	return (max);
}

void	ft_env_export(t_vars *vars)
{
	t_list	*lst;
	t_list	*min;
	int		i;

	i = ft_lst_counter(vars);
	ft_set_index(vars);
	while (i > 0)
	{
		min = ft_setmax(vars->env->next);
		lst = vars->env->next;
		while (lst)
		{
			if ((lst->index == -1)
				&& (ft_strcmp((char *)min->content, (char *)lst->content) > 0))
				min = lst;
			lst = lst->next;
		}
		if ((ft_strncmp((char *)min->content, "?=", 2) != 0)
			&& (ft_strncmp((char *)min->content, "_=", 2) != 0)
			&& (min->index == -1))
			ft_printexport((char *)min->content);
		min->index = 0;
		i--;
	}
	vars->exit_status = 0;
}
