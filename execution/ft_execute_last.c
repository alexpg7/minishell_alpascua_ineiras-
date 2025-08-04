/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_last.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:27:11 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/04 18:27:14 by alpascua         ###   ########.fr       */
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

/*static void	ft_set_redirlast(t_command *command, t_vars *vars, int mode)
{
	if (command->infile && (mode == 0 || mode == 2))
	{
		if (ft_readin(command->infile, command->hd) == -1)
			ft_exit(NULL, 1, vars);
	}
	if (command->outfile && (mode == 1 || mode == 2))
	{
		if (ft_readout(command->outfile, command->ap) == -1)
			ft_exit(NULL, 1, vars);
	}
}*/

void	ft_childlast(t_command *command, int *pip, t_vars *vars)
{
	char	*path;

	ft_checkfdpipe(pip[0], 0);
	close(pip[1]);
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

int	ft_execlast(t_command *comm, int *pid, int **pip, t_vars *vars)
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
			ft_childlast(comm, pip[0], vars);
			ft_exit(NULL, 0, vars);
		}
		close(pip[0][0]);
	}
	else
		pid[0] = -1;
	return (0);
}
