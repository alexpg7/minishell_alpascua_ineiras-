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

void	ft_copycommand(t_input **input, char **comm, int size)
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
		else if (flag  == 0)
			(*input)->token[i] = 'c';
		(*input)->word[i] = ft_strdup(comm[i]); // protect AND CLEAN STRING (looking at token)
		i++;
	}
	(*input)->word[i] = NULL;
	(*input)->token[i] = '\0';
}

void	ft_fillinput(t_input ***input, char **comm, t_vars *vars)
{
	int	i;
	int	size;

	i = 0;
	while (i < vars->np + 1)
	{
		size = ft_comsize(comm);
		(*input)[i] = (t_input *)malloc(sizeof(t_input)); // protect
		(*input)[i]->word = (char **)malloc(sizeof(char *) * (size + 1)); // protect
		(*input)[i]->token = (char *)malloc(sizeof(char) * (size + 1)); // protect
		ft_copycommand((*input + i), comm, size);
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
		ft_exit(NULL, 2, vars);
	}
	ft_fillinput(&input, comm, vars);
	return (input);
}
