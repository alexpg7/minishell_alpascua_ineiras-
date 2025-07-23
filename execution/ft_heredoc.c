#include "../src/minishell.h"

static char	ft_s1(char *str, int i, int len)
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
	while (ft_s1(s1, i, len) == s2[i] && ft_s1(s1, i, len) != '\0' && s2[i] != '\0')
		i++;
	return (ft_s1(s1, i, len) - s2[i]);
}

int	ft_writefile(char *lim, int fd)
{
	char	*text;

	ft_putstr_fd("heredoc> ", 0);
	text = get_next_line(0);
	if (!text)
	{
		perror("get_next_line");
		return (-1);
	}
	while (ft_strcmp2(lim, text) != 0)
	{
		ft_putstr_fd(text, fd);
		free(text);
		ft_putstr_fd("heredoc> ", 1);
		text = get_next_line(0);
		if (!text)
		{
			perror("get_next_line");
			return (-1);
		}
	}
	free(text);
	get_next_line(-1);
	return (0);
}

int	ft_heredoc(char *lim)
{
	int	fd;

	fd = open(".here_doc.tmp", O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		perror(".here_doc.tmp");
		return (-1);
	}
	return (ft_writefile(lim, fd));
}
