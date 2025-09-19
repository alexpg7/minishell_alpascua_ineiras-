#include "../src/minishell.h"

void	ft_printexport(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	ft_putstr_fd("declare -x ", 1);
	while(str[i])
	{
		if (str[i] == '=')
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
