/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:38:26 by alpascua          #+#    #+#             */
/*   Updated: 2025/09/19 16:38:28 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	ft_printexport(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	ft_putstr_fd("declare -x ", 1);
	while (str[i])
	{
		if (str[i] == '=' && flag == 0)
		{
			flag = 1;
			ft_putstr_fd("=\"", 1);
		}
		else if (str[i] == '\"')
			ft_putstr_fd("\\\"", 1);
		else
			ft_putchar_fd(str[i], 1);
		i++;
	}
	if (flag == 1)
		ft_putchar_fd('\"', 1);
	ft_putchar_fd('\n', 1);
}
