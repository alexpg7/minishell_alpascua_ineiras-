/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_execmore.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:46:08 by alpascua          #+#    #+#             */
/*   Updated: 2025/09/07 11:08:25 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	ft_child_3(t_input *input, char *here, t_vars *vars)
{
	char	*path;

	ft_set_redir_2(input, here, vars);
	vars->exit_status = 0;
	if (!ft_builtin_n(input, vars))
	{
		if (!ft_builtin_2(input, vars))
		{
			vars->envp = ft_getenv(vars->env);
			path = ft_findpath(input->comm[0], vars->envp, vars);
			if (!vars->envp || !path)
				ft_exit(path, vars->exit_status, vars);
			if (execve(path, input->comm, vars->envp) == -1)
				ft_exit(path, 1, vars);
		}
	}
}

void	ft_pipandclose(int **pip, int fd, t_vars *vars)
{
	if (fd == 1 || fd == 2)
	{
		if (dup2(pip[0][1], 1) == -1)
			ft_exit(NULL, 1, vars);
		close(pip[0][0]);
		close(pip[0][1]);
	}
	if (fd == 2)
	{
		if (dup2(pip[-1][0], 0) == -1)
			ft_exit(NULL, 1, vars);
		close(pip[-1][1]);
		close(pip[-1][0]);
	}
	if (fd == 0)
	{
		if (dup2(pip[0][0], 0) == -1)
			ft_exit(NULL, 1, vars);
		close(pip[0][1]);
		close(pip[0][0]);
	}
}

void	ft_new_execmore2(int num, int **pip, int fd, t_vars *vars)
{
	t_input	*input;

	input = vars->input[num];
	ft_command_array(input, vars);
	ft_signal(WAIT);
	input->pid = fork();
	if (input->pid == -1)
	{
		perror("fork");
		ft_exit(NULL, 1, vars);
	}
	else if (input->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
    	signal(SIGQUIT, SIG_DFL);
		ft_pipandclose(pip, fd, vars);
		ft_child_3(input, ft_sufix(vars->here, num), vars);
		ft_exit(NULL, vars->exit_status, vars);
	}
}

void	ft_while_execmore(t_input **input, int np, t_vars *vars)
{
	int	i;

	i = 1;
	while (i < np)
	{
		if (pipe(vars->pip[i]) == -1)
		{
			perror("pipe");
			ft_exit(NULL, 2, vars);
		}
		ft_makeheredoc(input[i], i, vars);
		ft_new_execmore2(i, &vars->pip[i], 2, vars);
		if (close(vars->pip[i][1]) == -1 || close(vars->pip[i - 1][0]) == -1)
		{
			perror("close");
			ft_exit(NULL, 1, vars);
		}
		i++;
	}
}

void	ft_new_execmore(t_input **input, t_vars *vars)
{
	vars->pip = ft_pipalloc(vars->np);
	if (!vars->np)
		ft_exit(NULL, 2, vars);
	if (pipe(vars->pip[0]) == -1)
	{
		perror("pipe");
		ft_exit(NULL, 2, vars);
	}
	ft_makeheredoc(input[0], 0, vars);
	ft_new_execmore2(0, &vars->pip[0], 1, vars);
	if (close(vars->pip[0][1]) == -42)
	{
		perror("close");
		ft_exit(NULL, 1, vars);
	}
	ft_while_execmore(input, vars->np, vars);
	ft_makeheredoc(input[vars->np], vars->np, vars);
	ft_new_execmore2(vars->np, &vars->pip[vars->np - 1], 0, vars);
	if (close(vars->pip[vars->np - 1][0]) == -42)
	{
		perror("close");
		ft_exit(NULL, 1, vars);
	}
	ft_waitall(input, vars->np + 1, vars);
	ft_signal(PROMPT);
}
