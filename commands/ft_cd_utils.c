#include "../src/minishell.h"

static int	slash_count(char *str)
{
	int	i;
	int count;

	i = 0;
	count = 0;
	while(str[i])
	{
		if (str[i] == '/')
		{
			count++;
		}
		i++;
	}
	return (count);
}

int count_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return i;
}

char	*minus_dir(char *dir, t_vars *vars)
{
	size_t	i;
	size_t	size;
	char *content;

	i = 0;
	size = ft_strlen(dir) - 1;
	if (size <= 5 || slash_count(dir) == 1)
	{
		content = ft_strjoin("PWD=", "/");
		if (!content)
			ft_exit(NULL, 1, vars);
		//free(dir);
		return (content);
	}
	while (dir[size - i] && ft_strncmp(&dir[size - i], "/", 1) != 0)
		i++;
	content = malloc(sizeof(char) * (size + 1));
	if (!content)
		ft_exit(NULL, 1, vars);
	ft_strlcpy(content, dir, (size - i + 1));
	//free(dir);
	return (content);
}

void	ft_putendl_fd2(char *s, int fd, char *var)
{
	ft_putstr_fd(s, fd);
	ft_putstr_fd(var, fd);
	ft_putchar_fd('\n', fd);
}

int	ft_free_minus_one(char *str)
{
	free(str);
	str = NULL;
	return (-1);
}