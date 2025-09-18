#include "../src/minishell.h"

void	ft_printexport(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		ft_putchar_fd(str[i], 1);
		if (str[i] == '=')
			ft_putchar_fd('\"', 1);
		if (str[i] == '\"')
			ft_putchar_fd('/', 1);
		i++;
	}
	ft_putchar_fd('\"', 1);
	ft_putchar_fd('\n', 1);
}