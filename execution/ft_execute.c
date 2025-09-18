/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:18:40 by alpascua          #+#    #+#             */
/*   Updated: 2025/09/07 11:14:35 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	ft_makeheredoc(t_input *input, int tag, t_vars *vars)
{
	int		i;
	int		fd;
	char	*path;

	i = 0;
	path = ft_sufix(vars->here, tag);
	while (input->token[i])
	{
		if (input->token[i] == 'h')
		{
			if (access(path, F_OK) == 0)
				unlink(ft_sufix(vars->here, tag));
			fd = ft_heredoc(input->word[i + 1], path, vars);
			if (fd == -1)
				ft_exit(NULL, NULL, 1, vars);
			if (close(fd) == -1)
				ft_exit(NULL, NULL, 1, vars);
		}
		i++;
	}
}

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
		unlink(ft_sufix(vars->here, i));
		vars->exit_status = exitstatus2(vars->exit_status);
		ft_printexit(vars->exit_status, i, vars);
		if (g_signal == SIGINT)
			vars->exit_status = 130;
		//g_signal = 0;
		i++;
	}
}

void	ft_child_2(t_input *input, char *here, t_vars *vars)
{
	char	*path;

	ft_set_redir_2(input, here, vars);
	vars->exit_status = 0;
	if (!ft_builtin_2(input, vars))
	{
		vars->envp = ft_getenv(vars->env);
		path = ft_findpath(input->comm[0], vars->envp, vars);
		if (!vars->envp || !path)
			ft_exit(path, NULL, vars->exit_status, vars);
		if (execve(path, input->comm, vars->envp) == -1)
			ft_exit(path, NULL, 1, vars);
	}
}

void	ft_new_exec(t_input *input, t_vars *vars)
{
	ft_command_array(input, vars);
	ft_makeheredoc(input, 0, vars);
	if (!ft_builtin_n(input, vars))
	{
		ft_signal(WAIT);
		input->pid = fork();
		if (input->pid == -1)
			perror("fork");
		else if (input->pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			ft_child_2(input, ft_sufix(vars->here, 0), vars);
			ft_exit(NULL, NULL, vars->exit_status, vars);
		}
		else
			ft_waitall(&input, 1, vars);
	}
	if (ft_search_tokken(input, 'h') > 0)
		unlink(ft_sufix(vars->here, 0));
}

void	ft_execute2(t_input **input, t_vars *vars)
{
	if (vars->np == 0)
		ft_new_exec(*input, vars);
	else
		ft_new_execmore(input, vars);
}
