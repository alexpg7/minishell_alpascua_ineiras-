#include "../../src/minishell.h"

int	ft_isspecial2(char *c)
{
	if (c[1] == '\0')
		return (0);
	if (*c == '\\')
	{
		if (c[1] == 'n') // EXTENSIBLE TO MORE CHARACTERS
			return ('\n');
	}
	return (0);
}

int	ft_countspecial(char *comm)
{
	int		i;
	int		count;
	char	c;

	i = 0;
	count = 0;
	c = '0';
	while (comm[i])
	{
		if (ft_isquote(comm[i]) && comm[i - (i != 0)] != '\\')
		{
			if (c == '0')
				c = comm[i];
			else if (c == comm[i])
				c = '0';
			i++;
			continue ;
		}
		if (ft_isspecial2(&comm[i]) && c != '0')
		{
			count++;
			i++;
			if (comm[i])
				i++;
		}
		else
			i++;
	}
	return (count);
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
		return (ft_strdup(comm));//protect
	quotes = 2 * ft_countquotes(comm); //number of quotes
	lenvars = ft_lenvars_clean(comm, vars); //difference when substituting vars
	lenvars += -ft_countspecial(comm);//difference when substituting special chars
	ft_printf("DIFFLEN: %i\n", lenvars);
	ft_printf("QUOTES: %i\n", quotes);
	return (ft_strdup(comm));//protect
}
