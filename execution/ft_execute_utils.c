/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:24:33 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/13 12:48:05 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	ft_set_redir(t_command *command, t_vars *vars, int mode)
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
}

int	ft_builtin2(t_command *com, t_vars *vars)
{
	char	*pwd;

	ft_set_redir(com, vars, 2);
	if (ft_strcmp("echo", com->comm[0]) == 0)
		ft_echo(com->comm + 1);
	else if (ft_strcmp("pwd", com->comm[0]) == 0)
	{
		pwd = ft_pwd(com->comm + 1, vars);
		if (pwd)
			ft_printf("%s\n", pwd);
	}
	else if (ft_strcmp("env", com->comm[0]) == 0)
		ft_env(vars);
	else
		return (0);
	return (1);
}

int	ft_builtin1(t_command *com, t_vars *vars)
{
	if (ft_strcmp("cd", com->comm[0]) == 0)
		ft_cd(vars, com->comm);
	else if (ft_strcmp("export", com->comm[0]) == 0)
		ft_export(vars, com->comm + 1, 0);
	else if (ft_strcmp("unset", com->comm[0]) == 0)
		ft_unset(com->comm + 1, vars);
	else if (ft_strcmp("exit", com->comm[0]) == 0)
		ft_exit(NULL, 0, vars);
	else
		return (0);
	return (1);
}

int	ft_searchbuiltin(t_command *com)
{
	if (ft_strcmp("cd", com->comm[0]) == 0)
		return (1);
	else if (ft_strcmp("export", com->comm[0]) == 0)
		return (1);
	else if (ft_strcmp("unset", com->comm[0]) == 0)
		return (1);
	else if (ft_strcmp("exit", com->comm[0]) == 0)
		return (1);
	return (0);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------
void	ft_set_redir_2(t_input *input, t_vars *vars)
{
	int	i;

	i = 0;
	while (input->word[i])
	{
		if (input->token[i] == 'i' && input->token[i + 1])
			ft_read_in(input, vars, i + 1);
		else if (input->token[i] == 'o')
			ft_read_out(input, vars, i + 1);
		else if (input->token[i] == 'a'  && input->token[i + 1])
			ft_read_app(input, vars, i + 1);
		else if (input->token[i] == 'h' && input->token[i + 1])
		{
			input->last_fd = ft_heredoc(input->word[i + 1]);
			if (input->last_fd == -1)
				ft_exit(NULL, 1, vars);
		}
	}
}

int	ft_builtin_2(t_input *input, t_vars *vars) 
{
	char	*pwd;

	if (input->command[0]) 
	{
		if (ft_strcmp("echo", input->command[0]) == 0)
			ft_echo(input->command[1]);
		else if (ft_strcmp("pwd", input->command) == 0)
		{
			pwd = ft_pwd(input->command + 1, vars); // We pass the input into PWD?
			if (pwd)
				ft_printf("%s\n", pwd);
		}
		else if (ft_strcmp("env", input->command[0]) == 0)
			ft_env(vars);
		else
			return (0);
	}
	return (1);
}


int	ft_searchbuiltin(t_command *com)
{
	if (ft_strcmp("cd", com->comm[0]) == 0)
		return (1);
	else if (ft_strcmp("export", com->comm[0]) == 0)
		return (1);
	else if (ft_strcmp("unset", com->comm[0]) == 0)
		return (1);
	else if (ft_strcmp("exit", com->comm[0]) == 0)
		return (1);
	return (0);
}

int	ft_builtin_n(t_input *input, t_vars *vars)
{
	if (!input->command)
		ft_exit(NULL, 0, vars);
	if (ft_strcmp("cd", input->command[0]) == 0)
		ft_cd(vars, input->command);
	else if (ft_strcmp("export", input->command[0]) == 0)
			ft_export(vars, input->command + 1, 0);
	else if (ft_strcmp("unset", input->command[0]) == 0)
		ft_unset(input->command + 1, vars);
	else if (ft_strcmp("exit", input->command[0]) == 0)
		ft_exit(NULL, 0, vars);
	else
		return (0);
	return (1);
}

void ft_command_array(t_input *input, t_vars *vars) // NEED TO ADD EVERYTHING TO THE TRASH LIST
{
	int	i = 0;
	int n;
	int	pos = 0;

	n = ft_tokken_counter(input, 'c');
	if (n == 0)
		return;
	input->command = malloc(sizeof(char*) * (n + 1));
	if (!input->command)
		ft_exit(NULL, 1, vars);
	while (i < n)
	{
		input->command[i] = ft_strdup(input->word[ft_search_tokken_2(input, 'c', &pos)]);
		if (!input->command[i])
			ft_exit(NULL, 1, vars);
		ft_printf("%s\n", input->command[i]); // Debug
		i++;
	}
	input->command[i] = NULL;
}