/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:42:28 by ineiras-          #+#    #+#             */
/*   Updated: 2025/08/04 16:55:51 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

static void	ft_echo_util(char **args, int *i, int *flag, int mode)
{
	if (*flag == 1)
		ft_putchar_fd(' ', 1);
	ft_printf("%s", args[*i]);
	*flag = 1;
	if (args[*i + 1] == NULL && mode != 1)
		ft_putchar_fd('\n', 1);
}

void	ft_echo(char **args)
{
	int	i;
	int	mode;
	int	flag;

	i = 0;
	mode = 0;
	flag = 0;
	if (!args[i])
	{
		ft_putchar_fd('\n', 1);
		return ;
	}
	if (ft_strcmp(args[i], "-n") == 0)
	{
		i++;
		mode = 1;
	}
	if (!args[i])
		return ;
	while (args[i])
	{
		ft_echo_util(args, &i, &flag, mode);
		i++;
	}
}
