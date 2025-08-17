#include "../../src/minishell.h"

void	ft_nextvar(char *comm, int *i)
{
	*i = *i + 1;
	while (comm[*i])
	{
		if (comm[*i] == '$')
			break ;
		*i = *i + 1;
	}
	*i = *i - 1;
}

int	ft_strcmpvar(char *var, char *name, int len)
{
	int	i;

	i = 0;
	while (var[i] == name[i] && var[i] && name[i] && i < len)
		i++;
	if (var[i] == '=' && i == len)
		return (0);
	return (var[i] - name[i]);
}

int	ft_isvar2(char *comm, int len, t_vars *vars)
{
	t_list	*env;

	env = vars->env;
	while (env)
	{
		if (ft_strcmpvar(env->content, comm, len) == 0)
			return (ft_strlen(ft_strchr(env->content, '=') + 1));
		env = env->next;
	}
	return (0);
}

int	ft_varlen2(char *comm, t_vars *vars)
{
	int	i;
	int	vallen;

	i = 0;
	vallen = 0;
	if (comm[0] == '?')
		return (ft_isvar2(comm + 1, 1, vars));
	//first, search the var len
	while (comm[i])
	{
		if (!ft_isalnum2(comm[i]))
			break ;
		i++;
	}
	vallen = ft_isvar2(comm, i, vars);
	return (vallen - i);
}

int	ft_lenvars(char *comm, t_vars *vars)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (comm[i])
	{
		if (comm[i] == '\'' && comm[i - (i != 0)] != '\\')
			ft_nextword2(comm, &i);
		else if (comm[i] == '$')
		{
			len += ft_varlen2(comm + 1, vars) - 1; // - 1 because of the '$'
			ft_nextvar(comm, &i);
		}
		if (comm[i])
			i++;
	}
	return len;
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
	lenvars = ft_lenvars(comm, vars); //difference when substituting vars
	//lenvars += difference when substituting special chars
	ft_printf("DIFFLEN: %i\n", lenvars);
	ft_printf("QUOTES: %i\n", quotes);
	return (ft_strdup(comm));//protect
}
