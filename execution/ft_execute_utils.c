/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:24:33 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/25 17:36:24 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	ft_openheredoc(char *path, t_input *input, int i, t_vars *vars)
{
	if (input->token[i] == 'h')
	{
		input->last_in = open(path, O_RDONLY);
		if (input->last_in == -1)
			ft_exit(NULL, NULL, 1, vars);
		if (dup2(input->last_in, STDIN_FILENO) == -1)
		{
			close(input->last_in);
			ft_exit(NULL, NULL, 1, vars);
		}
		if (close(input->last_in) == -1)
			ft_exit(NULL, NULL, 1, vars);
	}
}

void	ft_set_redir_2(t_input *input, char *path, t_vars *vars)
{
	int	i;

	i = 0;
	input->last_in = -42;
	input->last_out = -42;
	while (input->word[i])
	{
		if (input->token[i] == 'i')
			ft_read_in(input, vars, i + 1);
		else
			ft_openheredoc(path, input, i, vars);
		i++;
	}
	i = 0;
	while (input->word[i])
	{
		if (input->token[i] == 'o')
			ft_write_out(input, vars, i + 1);
		else if (input->token[i] == 'a')
			ft_read_app(input, vars, i + 1);
		i++;
	}
}

int	ft_builtin_2(t_input *input, t_vars *vars)
{
	char	*pwd;

	if (input->comm[0])
	{
		if (ft_strcmp("echo", input->comm[0]) == 0)
		{
			ft_echo(input->comm + 1);
			vars->exit_status = 0;
		}
		else if (ft_strcmp("pwd", input->comm[0]) == 0)
		{
			pwd = ft_new_pwd();
			if (pwd)
				ft_printf("%s\n", pwd);
			free(pwd);
		}
		else if (ft_strcmp("env", input->comm[0]) == 0)
			ft_env(vars);
		else
			return (0);
	}
	return (1);
}

int	ft_builtin_n(t_input *input, t_vars *vars)
{
	if (!input->comm)
		ft_exit(NULL, NULL, 0, vars);
	if (ft_strcmp("cd", input->comm[0]) == 0)
		ft_cd(vars, input->comm);
	else if (ft_strcmp("unset", input->comm[0]) == 0)
		ft_unset(input->comm + 1, vars);
	else if (ft_strcmp("export", input->comm[0]) == 0)
		ft_export(vars, input->comm + 1, 0);
	else if (ft_strcmp("exit", input->comm[0]) == 0)
		ft_exit(NULL, input->comm + 1, 0, vars);
	else
		return (0);
	return (1);
}

void	ft_command_array(t_input *input, t_vars *vars)
{
	int	i;
	int	n;
	int	pos;

	n = ft_tokken_counter(input, 'c');
	if (n == 0)
		return ;
	i = 0;
	pos = 0;
	input->comm = malloc(sizeof(char *) * (n + 1));
	if (!input->comm)
		ft_exit(NULL, NULL, 1, vars);
	while (input->token[i])
	{
		if (input->token[i] == 'c')
		{
			input->comm[pos] = input->word[i];
			pos++;
		}
		i++;
	}
	input->comm[pos] = NULL;
	i = 0;
}
