#include "../../src/minishell.h"

int	ft_lenvars(char *comm, t_vars *vars)
{
	comm = NULL;
	vars->np = vars->np;
	return 0;
}

int	ft_countquotes(char *comm)
{
	int		i;
	int		count;
	char	c;

	i = 0;
	count = 0;
	while (comm[i])
	{
		if (ft_isquote(comm[i]) && comm[i - (i != 0)] != '\\')
		{
			count++;
			c = comm[i];
			i++;
			while (comm[i] && !(comm[i] == c && comm[i - (i != 0)] != '\\'))
				i++;
		}
		if (comm[i])
			i++;
	}
	return (count);
}

char	*ft_cleanstring(char *comm, char token, t_vars *vars)
{
	int	quotes;
	int	lenvars;

	if (token != 'w' && token != 'c')
		return (ft_strdup(comm));
	quotes = 2 * ft_countquotes(comm);
	lenvars = ft_lenvars(comm, vars);
	ft_printf("QUOTES: %i\n", quotes);
	return (ft_strdup(comm));
}
