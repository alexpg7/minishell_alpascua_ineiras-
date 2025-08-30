/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputstruct_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 14:52:13 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/30 14:52:15 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/minishell.h"

int	ft_isredir(char *str)
{
	if (!str)
		return (0);
	if (ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0
		|| ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0)
	{
		return (1);
	}
	return (0);
}

int	ft_nextcommand(char **comm, int i)
{
	while (comm[i])
	{
		if (ft_isredir(comm[i]))
			i = i + 2;
		else if (ft_strcmp(comm[i], "|") != 0)
			return (1);
		else
			return (0);
	}
	return (0);
}

int	ft_checkpipes(char **comm)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (ft_strcmp(comm[0], "|") == 0)
		return (-1);
	if (ft_nextcommand(comm, 0) == 0)
		return (-1);
	while (comm[i])
	{
		if (ft_strcmp(comm[i], "|") == 0)
		{
			count++;
			if (ft_nextcommand(comm, i + 1) == 0)
				return (-1);
		}
		i++;
	}
	return (count);
}

int	ft_checkredirs(char **comm)
{
	int	i;

	i = 0;
	while (comm[i])
	{
		if (ft_isredir(comm[i]))
		{
			if (comm[i + 1])
			{
				if (ft_isredir(comm[i + 1]) || ft_strcmp(comm[i + 1], "|") == 0)
					return (-1);
			}
			else
				return (-1);
		}
		i++;
	}
	return (0);
}

int	ft_comsize(char **comm)
{
	int	i;

	i = 0;
	while (comm[i])
	{
		if (ft_strcmp(comm[i], "|") == 0)
			return (i);
		i++;
	}
	return (i);
}
