/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:17:17 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/13 19:45:29 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

int	ft_writefile(char *lim, int fd)
{
	char	*text;

	text = readline("heredoc> ");
	if (!text)
	{
		ft_putstr_fd("warning: heredoc finished with EOF instead of \"", 2);
		ft_putstr_fd(lim, 2);
		ft_putstr_fd("\"\n", 2);
		return (fd);
	}
	while (ft_strcmp(lim, text) != 0 && g_signal != SIGINT)
	{
		ft_putstr_fd(text, fd);
		ft_putchar_fd('\n', fd);
		text = readline("heredoc> ");
		if (!text)
		{
			ft_putstr_fd("warning: heredoc finished with EOF instead of \"", 2);
			ft_putstr_fd(lim, 2);
			ft_putstr_fd("\"\n", 2);
			return (fd);
		}
	}
	if (g_signal == SIGINT)
		unlink(".here_doc.tmp");
	ft_signal(WAIT);
	return (fd);
}

int	ft_heredoc(char *lim)
{
	int	fd;

	ft_signal(HEREDOC);
	fd = open(".here_doc.tmp", O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		perror(".here_doc.tmp");
		return (-1);
	}
	return (ft_writefile(lim, fd));
}
