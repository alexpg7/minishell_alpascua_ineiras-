/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanstring.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 13:58:38 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/30 13:58:42 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/minishell.h"

int	ft_isspecial2(char *c)
{
	if (c[1] == '\0')
		return (0);
	if (*c == '\\')
	{
		if (c[1] == 'n')
			return ('\n');
		else if (c[1] == 't')
			return ('\t');
		else if (c[1] == 'r')
			return ('\r');
		else if (c[1] == 'f')
			return ('\f');
		else if (c[1] == 'v')
			return ('\v');
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

char	*ft_searchvar(char *comm, int len, t_vars *vars)
{
	t_list	*env;

	env = vars->env;
	while (env)
	{
		if (ft_strcmpvar(env->content, comm, len) == 0)
			return (ft_strchr(env->content, '=') + 1);
		env = env->next;
	}
	return (NULL);
}

void	ft_copyvar(char **dest, char *src, int *i, t_vars *vars)
{
	int	len;
	int	varlen;

	if (src[*i + 1] == '?')
		len = 1;
	else
	{
		len = 0;
		while (src[*i + 1 + len])
		{
			if (!ft_isalnum2(src[*i + 1 + len]))
				break ;
			len++;
		}
	}
	varlen = ft_isvar_clean(&src[*i + 1], len, vars);
	if (varlen)
		ft_strlcpy(*dest, ft_searchvar(&src[*i + 1], len, vars), varlen + 1);
	*dest = *dest + varlen;
	*i = *i + len + 1;
}

char	ft_unquoted(char **dest, char *src, int *i, t_vars *vars)
{
	if (ft_isquote(src[*i]) && src[*i - (*i != 0)] != '\\')
	{
		*i = *i + 1;
		return (src[*i - 1]);
	}
	if (src[*i] == '$')
		ft_copyvar(dest, src, i, vars);
	else
	{
		**dest = src[*i];
		*i = *i + 1;
		*dest = *dest + 1;
	}
	return ('0');
}

char	ft_quoted1(char **dest, char *src, int *i)
{
	if (src[*i] == '\'' && src[*i - (*i != 0)] != '\\')
	{
		*i = *i + 1;
		return ('0');
	}
	if (ft_isspecial2(&src[*i]))
	{
		**dest = ft_isspecial2(&src[*i]);
		*dest = *dest + 1;
		*i = *i + 2;
	}
	else
	{
		**dest = src[*i];
		*i = *i + 1;
		*dest = *dest + 1;
	}
	return ('\'');
}

char	ft_quoted2(char **dest, char *src, int *i, t_vars *vars)
{
	if (src[*i] == '\"' && src[*i - (*i != 0)] != '\\')
	{
		*i = *i + 1;
		return ('0');
	}
	if (ft_isspecial2(&src[*i]))
	{
		**dest = ft_isspecial2(&src[*i]);
		*dest = *dest + 1;
		*i = *i + 2;
	}
	if (src[*i] == '$')
		ft_copyvar(dest, src, i, vars);
	else
	{
		**dest = src[*i];
		*i = *i + 1;
		*dest = *dest + 1;
	}
	return ('\"');
}

void	ft_copyclean(char *dest, char *src, t_vars *vars)
{
	int		i;
	char	c;

	i = 0;
	c = '0';
	while (src[i])
	{
		if (c == '0')
		{
			c = ft_unquoted(&dest, src, &i, vars);
			continue ;
		}
		else if (c == '\'')
		{
			c = ft_quoted1(&dest, src, &i);
			continue ;
		}
		else if (c == '\"')
		{
			c = ft_quoted2(&dest, src, &i, vars);
			continue ;
		}
	}
	*dest = '\0';
}

char	*ft_cleanstring(char *comm, char token, t_vars *vars)
{
	int		lendiff;
	char	*ptr;
	char	*dupcomm;

	if (token != 'w' && token != 'c')
	{
		dupcomm = ft_strdup(comm);
		if (!dupcomm)
			ft_exit(NULL, 2, vars);
		return (dupcomm);
	}
	lendiff = - 2 * ft_countquotes(comm); //number of quotes
	lendiff = ft_lenvars_clean(comm, vars); //difference when substituting vars
	lendiff += -ft_countspecial(comm);//difference when substituting special chars
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(comm) + lendiff + 1));
	if (!ptr)
		ft_exit(NULL, 2, vars);
	ft_copyclean(ptr, comm, vars);
	return (ptr);
}
