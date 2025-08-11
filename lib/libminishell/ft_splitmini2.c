#include "../../src/minishell.h"

void	ft_nextword(char *str, int *i)
{

}

int	ft_countwords2(char *str)
{
	int	i;
	int	count;

	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i])
		{
			count++;
			ft_nextword2(str, &i);
		}
	}
	return (count);
}

char	**ft_splitmini2(char *str, t_vars *vars)
{
	int	words;

	vars->np = 0;
	words = ft_countwords2(str);
	ft_printf("%i\n", words);
}
