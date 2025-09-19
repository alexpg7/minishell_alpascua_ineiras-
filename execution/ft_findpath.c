/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_findpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:22:42 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/04 18:22:45 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../src/minishell.h"

static char	*ft_path2(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
	{
		i++;
	}
	if (envp[i])
		return (envp[i] + 5);
	ft_putstr_fd("no PATH variable found.\n", 2);
	return (NULL);
}

static char	*ft_checkpath(char **paths, char *comm, int *ret)
{
	int		i;
	char	*program;

	i = 0;
	while (paths[i])
	{
		program = ft_strjoin3(paths[i], "/", comm);
		if (!program)
		{
			*ret = -1;
			return (NULL);
		}
		if (access(program, F_OK) == 0)
		{
			if (access(program, X_OK) == 0)
				return (program);
			*ret = 126;
		}
		free(program);
		i++;
	}
	*ret = 127;
	return (NULL);
}

static char	*ft_findpath2(char *comm2, char **envp, t_vars *vars)
{
	int		ret;
	char	*ptr;
	char	**path;
	char	*pathvar;

	ret = 0;
	pathvar = ft_path2(envp);
	if (!pathvar)
		path = ft_split(" ", 'c');
	else
		path = ft_split(pathvar, ':');
	if (!path)
		ft_exit(comm2, NULL, 1, vars);
	ptr = ft_checkpath(path, comm2, &ret);
	ft_freestrarr(&path, 1);
	if (ret != 0)
		ft_exit(comm2, NULL, ret, vars);
	free(comm2);
	return (ptr);
}

int	ft_checkstat(char *path, t_vars *vars)
{
	struct stat	st;

	stat(path, &st);
	if (S_ISDIR(st.st_mode))
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": is a directory.\n", 2);
		vars->exit_status = 126;
		free(path);
		return (1);
	}
	else if (S_ISREG(st.st_mode))
		return (0);
	else
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": not a file or directory.\n", 2);
		free(path);
		vars->exit_status = 127;
		return (1);
	}
	return (0);
}

char	*ft_findpath(char *comm, char **envp, t_vars *vars)
{
	char	*comm2;

	comm2 = ft_strdup(comm);
	if (!comm2)
		ft_exit(NULL, NULL, 1, vars);
	if (comm2[0] == '.' || comm2[0] == '/')
	{
		if (ft_checkstat(comm2, vars) == 0)
		{
			if (access(comm2, F_OK) == 0)
			{
				if (access(comm2, X_OK) == 0)
					return (comm2);
				else
					vars->exit_status = 126;
				free(comm2);
				return (NULL);
			}
		}
		else
			return (NULL);
	}
	return (ft_findpath2(comm2, envp, vars));
}
