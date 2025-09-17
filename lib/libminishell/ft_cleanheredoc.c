/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanheredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:36:52 by alpascua          #+#    #+#             */
/*   Updated: 2025/09/17 16:36:55 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/minishell.h"

static char	ft_unquotedhere(char **dest, char *src, int *i, t_vars *vars)
{
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

static void	ft_copycleanhere(char *dest, char *src, t_vars *vars)
{
	int	i;

	i = 0;
	while (src[i])
		ft_unquotedhere(&dest, src, &i, vars);
	*dest = '\0';
}

static int	ft_lenvars_heredoc(char *comm, t_vars *vars)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (comm[i])
	{
		if (comm[i] == '$' && ft_isalnum2(comm[i + 1]))
		{
			len += ft_varlen_clean(&comm[i + 1], vars) - 1;
			ft_nextvar(comm, &i);
		}
		else if (comm[i])
			i++;
	}
	return (len);
}

char	*ft_cleanheredoc(char *comm, char token, t_vars *vars)
{
	int		lendiff;
	char	*ptr;
	char	*dupcomm;

	if (token != 'w' && token != 'c')
	{
		dupcomm = ft_strdup(comm);
		if (!dupcomm)
			ft_exit(NULL, NULL, 1, vars);
		return (dupcomm);
	}
	lendiff = ft_lenvars_heredoc(comm, vars);
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(comm) + lendiff + 1));
	if (!ptr)
		ft_exit(NULL, NULL, 1, vars);
	ft_copycleanhere(ptr, comm, vars);
	return (ptr);
}
