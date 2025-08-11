/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:24:33 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/11 18:47:40 by ineiras-         ###   ########.fr       */
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
void	ft_set_redir_2(t_input *input, t_vars *vars, int mode)
{
	int	i;
	int in = search_tokken(input, 'i');
	int out = search_tokken(input, 'o');
	int here_d = search_tokken(input, 'h');
	int	app = search_tokken(input, 'a');

	while ((input->word[i]) && ((input->token[i] == 'i') || (input->token[i] == 'o') || (input->token[i] == 'h')))
	{
		if (input->token[i] == 'i')
		{
			ft_read_in(); // if -1 exit;
		}
		else if (input->token[i] == 'o')
		{
				ft_read_out(); // if -1 exit;
		}
		else if (input->token[i] == 'h')
		{
				ft_read_heare(); // Maybe it fits on the same logic as read_in(); // if -1 exit;
		}
		else
		{
				ft_read_app(); // Same logic as read_in but appending instead; // if -1 exit;
		}	
	}
	/*
	if ((in > 0 ) && (mode == 0 || mode == 2))
	{
		if (ft_readin(input->word[in + 1], here_d) == -1)
			ft_exit(NULL, 1, vars);
	}
	if ((out > 0) && (mode == 1 || mode == 2))
	{
		if (ft_readout(input->word[out + 1], app) == -1)
			ft_exit(NULL, 1, vars);
	}
	*/
}

int	ft_builtin_2(t_input *input, t_vars *vars) 
{
	char	*pwd;
	int		comm = search_tokken(input, 'c');

	ft_set_redir(input, vars, 2);
	if (comm >= 0) 
	{
		if (ft_strcmp("echo", input->word[comm]) == 0)
			ft_echo(input->word[comm + 1]);
		else if (ft_strcmp("pwd", input->word[comm]) == 0)
		{
			pwd = ft_pwd(input->word[comm + 1], vars); // We pass the input into PWD?
			if (pwd)
				ft_printf("%s\n", pwd);
		}
		else if (ft_strcmp("env", input->word[comm]) == 0)
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
	int command;

	command = search_tokken(input, 'c');
	if (command != 0)
	{
		if (ft_strcmp("cd", input->command[0]) == 0)
			ft_cd(vars, input->word[command]);
		else if (ft_strcmp("export", input->command[0]) == 0)
			ft_export(vars, input->word[command] + 1, 0);
		else if (ft_strcmp("unset", input->command[0]) == 0)
			ft_unset(input->word[command] + 1, vars);
		else if (ft_strcmp("exit", input->command[0]) == 0)
			ft_exit(NULL, 0, vars);
		else
			return (0); // Why this?
	}
	return (1);
}
void ft_command_array(t_input *input, t_vars *vars)
{
	int	i = 0;
	int n = tokken_counter(input, 'c');
	int	pos = 0;

	input->command = malloc((sizeof(char**) * n ) + 1);
	if (!(*input->command))
		ft_exit(NULL, 1, vars);
	while (i < n)
	{
		input->command[i] = ft_strdup(input->word[search_tokken(input, 'c', &pos)]);
		ft_printf("%s\n", input->command[i]);
		i++;
	}
	input->command[i] = NULL;
}