/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:17:17 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/04 18:17:21 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../src/minishell.h"

/*static char	ft_s1(char *str, int i, int len)
{
	if (i < len)
		return (str[i]);
	if (i == len)
		return ('\n');
	return ('\0');
}

static int	ft_strcmp2(char *s1, char *s2)
{
	size_t	i;
	int		len;

	i = 0;
	len = ft_strlen(s1);
	while (ft_s1(s1, i, len) == s2[i]
		&& ft_s1(s1, i, len) != '\0' && s2[i] != '\0')
	{
		i++;
	}
	return (ft_s1(s1, i, len) - s2[i]);
}*/

int	ft_writefile(char *lim, int fd)
{
	char	*text;

	text = readline("heredoc> ");
	if (!text)
	{
		ft_putstr_fd("warning: heredoc finished with EOF instead of \"", 2);
		ft_putstr_fd(lim, 2);
		ft_putstr_fd("\"\n", 2);
		return (0);
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
			return (0);
		}
	}
	ft_signal(WAIT);
	return (0);
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
