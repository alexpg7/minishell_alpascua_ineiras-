/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_1command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:37:39 by alpascua          #+#    #+#             */
/*   Updated: 2025/09/19 16:37:41 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_arrlen(int narg, char **argv)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i < narg)
	{
		len += ft_strlen(argv[i]);
		len++;
		i++;
	}
	return (len);
}

void	ft_copyarr(char *dest, char **src, int narg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < narg)
	{
		ft_strlcpy(dest + j, src[i], ft_strlen(src[i]) + 1);
		*(dest + j + ft_strlen(src[i])) = ' ';
		*(dest + j + ft_strlen(src[i]) + 1) = '\0';
		j += ft_strlen(src[i]) + 1;
		i++;
	}
}

int	ft_1command(int narg, char **argv, t_vars *vars)
{
	char	*comm;
	int		len;

	len = ft_arrlen(narg, argv);
	comm = (char *)malloc(sizeof(char) * (len + 1));
	if (!comm)
		ft_exit(NULL, NULL, 1, vars);
	ft_copyarr(comm, argv, narg);
	do_stuff(comm, 1, vars);
	ft_exit(NULL, NULL, vars->exit_status, vars);
	return (vars->exit_status);
}
