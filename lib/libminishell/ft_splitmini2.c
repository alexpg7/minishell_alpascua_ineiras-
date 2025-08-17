#include "../../src/minishell.h"

int	ft_isop(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int	ft_isquote(char c)
{
	if (c == '\"' || c == '\'')
		return (1);
	return (0);
}

int	ft_checkop(char *str, int *i)
{
	if (ft_isop(str[*i]))
	{
		if (str[*i] == '>' || str[*i] == '<')
		{
			if (str[*i] == str[*i + 1])
				*i = *i + 1;
		}
		*i = *i + 1;
		return (1);
	}
	return (0);
}

int	ft_nextword2(char *str, int *i)
{
	char	c;
	int		k;

	c = '0';
	k = *i;
	if (ft_checkop(str, i))
		return (*i - k);
	while (str[*i])
	{
		if (c == '0' && ft_isop(str[*i]))
			return (*i - k);
		else if (c == '0' && ft_isquote(str[*i]) && str[*i - (*i != 0)] != '\\')
		{
			if (str[*i - (*i != 0)] != '\\')
			{
				c = str[*i];
				*i = *i + 1;
			}
		}
		else if (c == '0' && !ft_isspace(str[*i]))
			*i = *i + 1;
		else if (c == '0' && ft_isspace(str[*i]))
			return (*i - k);
		else if (c != '0')
		{
			if (str[*i] == c && str[*i - (*i != 0)] != '\\')
				c = '0';
			*i = *i + 1;
		}
	}
	if (c != '0')
	{
		ft_putstr_fd("parsing error: unclosed quotes\n", 2);
		return (-1);
	}
	return (*i - k);
}

int	ft_countwords2(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i])
		{
			count++;
			if (ft_nextword2(str, &i) == -1)
				return (-1);
		}
	}
	return (count);
}

char	**ft_splitmini2(char *str, t_vars *vars)
{
	int		words;
	int		i;
	int		k;
	int		j;
	char	**ptr;

	vars->np = 0;
	words = ft_countwords2(str);
	if (words == -1)
		return (NULL);
	ptr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!ptr)
		ft_exit(NULL, 2, vars);
	i = 0;
	j = 0;
	while (i < words)
	{
		while (ft_isspace(str[j]))
			j++;
		k = j;
		ptr[i] = ft_substr(str, k, ft_nextword2(str, &j));
		if (!ptr[i])
			return (ft_free(ptr, i));
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}
