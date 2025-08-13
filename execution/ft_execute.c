/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:18:40 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/13 13:20:03 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

/*
void	ft_child(t_command *command, t_vars *vars)
{
	char	*path;

	vars->exit_status = 0;
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

void	ft_exec1(t_command *command, t_vars *vars)
{
	int		pid;

	if (command->hd == 1)
	{
		if (ft_heredoc(command->infile) == -1)
			ft_exit(NULL, 1, vars);
	}
	if (!ft_builtin1(command, vars))
	{
		ft_signal(WAIT);
		pid = fork();
		if (pid == -1)
			perror("fork");
		else if (pid == 0)
		{
			ft_child(command, vars);
			ft_exit(NULL, vars->exit_status, vars);
		}
		else
			ft_waitall(&pid, 1, vars);
	}
	if (command->hd == 1)
		unlink(".here_doc.tmp");
}

void	ft_execute(t_command *command, t_vars *vars)
{
	if (vars->np == 0)
		ft_exec1(command, vars);
	else
		ft_execmore(command, vars);
}
*/
//--------------------------------------------------------------------------------------------------------------------
/*
void	ft_exec2(t_input *input, t_vars *vars)
{
	int		pid;

	if (ft_search_tokken(input, 'h') >= 0)
	{
		if (ft_heredoc(input->word[ft_search_tokken(input, 'h') + 1]) == -1) 
			ft_exit(NULL, 1, vars);
	}

	ft_command_array(input, vars);
	if (!ft_builtin_n(input, vars))
	{
		ft_signal(WAIT);
		pid = fork();
		if (pid == -1)
			perror("fork");
		else if (pid == 0)
		{
			ft_child_2(input, vars);
			ft_exit(NULL, vars->exit_status, vars);
		}
		else
			ft_waitall(&pid, 1, vars);
	}
	if (ft_search_tokken(input, 'h') > 0)
		unlink(".here_doc.tmp");
}*/


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
	int		fd;
	int		i;

	input->last_fd = -1;
	while (i < ft_input_count(input->word))
	{
		if (input->token[i] == 'h' && input->token[i + 1])
		{
			if (input->last_fd >= 0)
				close(input->last_fd);
			input->last_fd = ft_heredoc(input->word[i + 1]);
			if (input->last_fd == -1)
				ft_exit(NULL, 1, vars);
		}
		i++;
	}
	ft_command_array(input, vars);
	if (!ft_builtin_n(input, vars))
	{
		ft_signal(WAIT);
		pid = fork();
		if (pid == -1)
			perror("fork");
		else if (pid == 0)
		{
			ft_child_2(input, vars);
			ft_exit(NULL, vars->exit_status, vars);
		}
		else
			ft_waitall(&pid, 1, vars);
	}
	if (ft_search_tokken(input, 'h') > 0)
		unlink(".here_doc.tmp");
}

void	ft_execute2(t_input *input, t_vars *vars)
{
	if (vars->np == 0)
		ft_exec2(input, vars);
	else
		ft_printf("next\n");
		//ft_execmore(command, vars); 
}
