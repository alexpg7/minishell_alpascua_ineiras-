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

int	ft_echonext(char **args, int i)
{
	char	c;

	if (!args[i + 1])
		return (0);
	c = args[i + 1][0];
	if (c == '|' || c == '<' || c == '>')
		return (0);
	else
		return (1);
}

void	ft_echo_util(char **args, int *i, int flag, int mode)
{
	if (flag == 1)
		ft_putchar_fd(' ', 1);
	ft_printf("%s", args[*i]);
	flag = 1;
	if (!ft_echonext(args, *i))
	{
		if (mode == 1)
			ft_putchar_fd('%', 1);
		ft_putchar_fd('\n', 1);
	}
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
		return ;
	if (ft_strncmp(args[i], "-n", 2) == 0 && ft_strlen(args[i]) == 2)
	{
		i++;
		mode = 1;
	}
	if (!args[i])
		return ;
	while (args[i])
	{
		ft_echo_util(args, &i, flag, mode);
		i++;
	}
}
