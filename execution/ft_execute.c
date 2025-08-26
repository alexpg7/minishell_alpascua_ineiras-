/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:18:40 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/25 18:41:50 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"


void	ft_waitall(t_input **input, int len, t_vars *vars)
{
	int	i;

	i = 0;
	while (i < len)
	{
		ft_signal(WAIT);
		if (input[i]->pid > 0)
			waitpid(input[i]->pid, &vars->exit_status, 0);
		ft_signal(PROMPT);
		unlink(".here_doc.tmp");
		vars->exit_status = exitstatus2(vars->exit_status);
		ft_printexit(vars->exit_status, i, vars);
		i++;
	}
}

void	ft_child_2(t_input *input, t_vars *vars)
{
	char	*path;

	ft_set_redir_2(input, vars);
	vars->exit_status = 0;
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

void	ft_new_exec(t_input *input, t_vars *vars) // Allways assuming that string is correct.
{
	ft_command_array(input, vars);
	if (!ft_builtin_n(input, vars))
	{
		ft_signal(WAIT);
		input->pid = fork();
		if (input->pid == -1)
			perror("fork");
		else if (input->pid == 0)
		{
			ft_child_2(input, vars);
			ft_exit(NULL, vars->exit_status, vars);
		}
		else
			ft_waitall(&input, 1, vars);
	}
	if (ft_search_tokken(input, 'h') > 0)
		unlink(".here_doc.tmp");
	//ft_freestrarr(&input->comm, 0); Free here if its not done outside.
}

void	ft_execute2(t_input **input, t_vars *vars)
{
	if (vars->np == 0)
		ft_new_exec(*input, vars);
	else
		ft_new_execmore(input, vars);
}
