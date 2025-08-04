/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_between.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:28:38 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/04 18:28:40 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../src/minishell.h"

static int	ft_checkfdpipe(int pipe, int final)
{
	if (dup2(pipe, final) == -1)
	{
		perror("dup2");
		close(pipe);
		return (-1);
	}
	close(pipe);
	return (0);
}

void	ft_childbetween(t_command *command, int *pip0, int *pip1, t_vars *vars)
{
	char	*path;

	ft_checkfdpipe(pip1[1], 1);
	close(pip0[1]);
	ft_checkfdpipe(pip0[0], 0);
	close(pip1[0]);
	if (!ft_builtin2(command, vars))
	{
		vars->envp = ft_getenv(vars->env);
		path = ft_findpath(command->comm[0], vars->envp, vars);
		if (!vars->envp || !path)
			ft_exit(path, vars->exit_status, vars);
		if (execve(path, command->comm, vars->envp) == -1)
			ft_exit(path, 1, vars);
	}
}

int	ft_execbetween(t_command *comm, int *pid, int **pip, t_vars *vars)
{
	if (comm->hd == 1)
	{
		if (ft_heredoc(comm->infile) == -1)
			ft_exit(NULL, 1, vars);
	}
	if (!ft_searchbuiltin(comm))
	{
		pid[0] = fork();
		if (pid[0] == -1)
			perror("fork");
		else if (pid[0] == 0)
		{
			ft_childbetween(comm, pip[0], pip[1], vars);
			ft_exit(NULL, 0, vars);
		}
		close(pip[0][0]);
		close(pip[1][1]);
	}
	else
		pid[0] = -1;
	return (0);
}
