/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_searchdollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:25:29 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/04 16:25:32 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../src/minishell.h"

static int	ft_calclen(char *str, t_vars *vars)
{
	int	i;

	i = 0;
	while (!ft_isvar(&str[i], vars, 1))
		i++;
	vars->dollar.vallen = ft_valuelen(&str[i + 1], vars);
	vars->dollar.varlen = ft_isvar(&str[i], vars, 1);
	return (vars->dollar.vallen - vars->dollar.varlen);
}

static void	ft_copyvar(char *dest, t_vars *vars)
{
	int		len;
	int		i;
	char	*val;

	len = vars->dollar.vallen;
	i = 0;
	val = vars->dollar.value;
	while (i < len)
	{
		dest[i] = val[i];
		i++;
	}
}

static char	*ft_subs2(char *str, char *ptr, t_vars *vars)
{
	int		i;
	int		valuelen;

	i = 0;
	valuelen = -1;
	while (*str)
	{
		if (ft_isvar(str, vars, 1) && valuelen == -1)
		{
			valuelen = vars->dollar.vallen;
			ft_copyvar(&ptr[i], vars);
			i = i + valuelen;
			str = str + vars->dollar.varlen;
		}
		else
		{
			ptr[i] = *str;
			str++;
			i++;
		}
	}
	ptr[i] = '\0';
	return (ptr);
}

static char	*ft_subs1(char *str, t_vars *vars)
{
	int		len;
	char	*ptr;

	len = ft_strlen(str) + ft_calclen(str, vars);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		ft_exit(NULL, 1, vars);
	return (ft_subs2(str, ptr, vars));
}

char	*ft_searchdollar(char *str, t_vars *vars)
{
	int		count;
	char	*new;
	char	*aux;

	new = str;
	if (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
		return (str);
	count = ft_countvars(str, vars);
	while (count > 0)
	{
		aux = new;
		new = ft_subs1(new, vars);
		free(aux);
		if (!new)
			ft_exit(NULL, 1, vars);
		count--;
	}
	return (new);
}
