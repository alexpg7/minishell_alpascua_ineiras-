/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputstruct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 14:10:49 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/30 14:10:51 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/minishell.h"

char	ft_redirtoken(char *comm)
{
	if (ft_strcmp(comm, ">") == 0)
		return ('o');
	else if (ft_strcmp(comm, "<") == 0)
		return ('i');
	else if (ft_strcmp(comm, ">>") == 0)
		return ('a');
	else if (ft_strcmp(comm, "<<") == 0)
		return ('h');
	return ('w');
}

void	ft_copycommand(t_input **input, char **comm, int size, t_vars *vars)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (i < size)
	{
		if (ft_isredir(comm[i]))
		{
			(*input)->token[i] = ft_redirtoken(comm[i]);
			flag = 1;
		}
		else if (flag == 1)
		{
			flag = 0;
			(*input)->token[i] = 'w';
		}
		else if (flag == 0)
			(*input)->token[i] = 'c';
		(*input)->word[i] = ft_cleanstring(comm[i], (*input)->token[i], vars);
		i++;
	}
	(*input)->word[i] = NULL;
	(*input)->token[i] = '\0';
}

static void	ft_fillinput2(t_input ***input, char **comm, int i, t_vars *vars)
{
	int	size;

	size = ft_comsize(comm);
	(*input)[i] = (t_input *)malloc(sizeof(t_input));
	if (!(*input)[i])
		ft_exit(NULL, NULL, 1, vars);
	(*input)[i]->comm = NULL;
	(*input)[i]->word = (char **)malloc(sizeof(char *) * (size + 1));
	(*input)[i]->token = (char *)malloc(sizeof(char) * (size + 1));
	if (!(*input)[i]->word || !(*input)[i]->token)
		ft_exit(NULL, NULL, 1, vars);
	ft_copycommand((*input + i), comm, size, vars);
}

void	ft_fillinput(t_input ***input, char **comm, t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->np + 1)
	{
		ft_fillinput2(input, comm, i, vars);
		while (*comm)
		{
			if (ft_strcmp(*comm, "|") == 0)
			{
				comm++;
				break ;
			}
			comm++;
		}
		i++;
	}
}

t_input	**ft_inputstruct(char **comm, t_vars *vars)
{
	t_input	**input;
	int		np;

	if (ft_checkredirs(comm) == -1)
	{
		ft_putstr_fd("parsing error: wrong redirecitons\n", 2);
		return (NULL);
	}
	np = ft_checkpipes(comm);
	if (np == -1)
	{
		ft_putstr_fd("parsing error: no command in pipe\n", 2);
		return (NULL);
	}
	vars->np = np;
	input = (t_input **)malloc(sizeof(t_input *) * (np + 1));
	if (!input)
	{
		ft_freestrarr(&comm, 0);
		ft_exit(NULL, NULL, 1, vars);
	}
	ft_fillinput(&input, comm, vars);
	return (input);
}
