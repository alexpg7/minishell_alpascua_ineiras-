/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:17:17 by alpascua          #+#    #+#             */
/*   Updated: 2025/09/07 11:18:58 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

static void	ft_message(char *lim, t_vars *vars)
{
	ft_putstr_fd("warning: heredoc finished with EOF instead of \"", 2);
	ft_putstr_fd(lim, 2);
	ft_putstr_fd("\"\n", 2);
	vars->exit_status = 130;
}

char	*ft_sufix(char *path, int tag)
{
	path[10] = '0' + (tag / 100) % 10;
	path[11] = '0' + (tag / 10) % 10;
	path[12] = '0' + (tag % 10);
	return (path);
}

int	ft_writefile(char *lim, char *path, int fd, t_vars *vars)
{
	char	*text;

	text = readline("heredoc> ");
	if (!text)
	{
		ft_message(lim, vars);
		return (fd);
	}
	while (ft_strcmp(lim, text) != 0 && g_signal != SIGINT)
	{
		ft_putstr_fd(text, fd);
		ft_putchar_fd('\n', fd);
		text = readline("heredoc> ");
		if (!text)
		{
			ft_message(lim, vars);
			return (fd);
		}
	}
	if (g_signal == SIGINT)
		unlink(path);
	ft_signal(WAIT);
	return (fd);
}

int	ft_heredoc(char *lim, char *path, t_vars *vars)
{
	int	fd;

	ft_signal(HEREDOC);
	fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		perror(path);
		return (-1);
	}
	return (ft_writefile(lim, path, fd, vars));
}
