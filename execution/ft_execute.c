/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:18:40 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/13 16:47:00 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	ft_child_2(t_input *input, t_vars *vars)
{
	char	*path;

	ft_set_redir_2(input, vars);
	vars->exit_status = 0;
	if (!ft_builtin_2(input, vars))
	{
		vars->envp = ft_getenv(vars->env);
		path = ft_findpath(input->command[0], vars->envp, vars);
		if (!vars->envp || !path)
			ft_exit(path, vars->exit_status, vars);
		if (execve(path, input->command, vars->envp) == -1)
			ft_exit(path, 1, vars);
	}
}

void	ft_new_exec(t_input *input, t_vars *vars) // Allways assuming that string is correct.
{
	int		pid;

	ft_command_array(input, vars);
	if (!ft_builtin_n(input, vars))
	{
		ft_signal(WAIT);
		pid = fork();
		if (pid == -1)
			perror("fork");
		else if (pid == 0)
		{
			ft_printf("Yea\n");
			ft_child_2(input, vars);
			ft_printf("Yea\n");
			ft_exit(NULL, vars->exit_status, vars);
		}
		else
			//ft_waitall(&pid, 1, vars);
			wait(NULL);
	}
	if (ft_search_tokken(input, 'h') > 0)
		unlink(".here_doc.tmp");
}

void	ft_execute2(t_input *input, t_vars *vars)
{
	if (vars->np == 0)
		ft_new_exec(input, vars);
	else
		ft_printf("next\n");
		//ft_execmore(command, vars); 
}
