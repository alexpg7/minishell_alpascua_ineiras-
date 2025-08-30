/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 18:02:36 by ineiras-          #+#    #+#             */
/*   Updated: 2025/08/30 18:04:36 by ineiras-         ###   ########.fr       */
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
