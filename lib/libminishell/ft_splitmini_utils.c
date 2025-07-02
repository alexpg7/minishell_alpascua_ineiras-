#include "../Libft/libft.h"
#include "libminishell.h"
#include <stdio.h>

void	ft_jumpcom(char const *s, int *i, char sep)
{
	char	c;

	while (s[*i] && s[*i] != sep)
	{
		if (s[*i] == '\"' || s[*i] == '\'')
		{
			c = s[*i];
			*i = *i + 1;
			while (s[*i] != c)
				*i = *i + 1;
			*i = *i + 1;
		}
	}
}

int	ft_special(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

void	ft_nextword(const char *s, int *i, char sep)
{
	if (s[*i] == '\'' || s[*i] == '\"')
	{
		ft_jumpcom(s, i, sep);
		return ;
	}
	else if (s[*i] == '|')
	{
		*i = *i + 1;
		return ;
	}
	else if (s[*i] == '>')
	{
		*i = *i + 1 + (s[*i + 1] == '>');
		return ;
	}
	else if (s[*i] == '<')
	{
		*i = *i + 1 + (s[*i + 1] == '<');
		return ;
	}
	while (s[*i] != ' ' && !ft_special(s[*i]) && s[*i])
		*i = *i + 1;
}
