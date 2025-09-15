/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 20:05:01 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/25 19:58:47 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

void	ft_newexit(t_vars *vars)
{
	char	*num;
	char	*com;

	if (vars->pip)
	{
		ft_freepip(vars->pip, vars->np, vars->np + 1);
		vars->pip = NULL;
	}
	num = ft_itoa(vars->exit_status);
	if (!num)
		ft_exit(NULL, NULL, 1, vars);
	com = ft_strjoin("?=", num);
	if (!com)
		ft_exit(num, NULL, 1, vars);
	free(num);
	if (!com)
		ft_exit(NULL, NULL, 1, vars);
	ft_export(vars, &com, 1);
}

/*void	ft_printcom(t_command *comm)
{
	int	i;
	int	j;

	i = 0;
	while (comm[i].comm)
	{
		ft_printf("-PIPE %i:\n", i + 1);
		j = 0;
		while (comm[i].comm[j])
		{
			ft_printf("%s\n", comm[i].comm[j]);
			j++;
		}
		ft_printf("-RED IN: %s, mode: %i\n", comm[i].infile, comm[i].hd);
		ft_printf("-RED OUT: %s, mode: %i\n\n", comm[i].outfile, comm[i].ap);
		i++;
	}
}

void	ft_freecommand(t_command *command)/////////////////////////
{
	int	i;

	i = 0;
	while (command[i].comm)
	{
		free(command[i].comm);
		i++;
	}
	free(command);
}*/

void	ft_freeinput(t_input ***input, int np, t_vars *vars)
{
	int	i;

	i = 0;
	while (i < np + 1)
	{
		if ((*input)[i]->token)
			free((*input)[i]->token);
		if ((*input)[i]->word)
			ft_freestrarr(&(*input)[i]->word, 0);
		if ((*input)[i]->comm)
			free((*input)[i]->comm);
		free((*input)[i]);
		i++;
	}
	free(*input);
	*input = NULL;
	vars->input = NULL;
}

void	do_stuff(char *str, t_vars *vars)
{
	char	**comm;
	t_input	**input;

	vars->np = 0;
	comm = ft_splitmini2(str, vars);
	if (!comm)
	{
		add_history(str);
		return ;
	}
	if (comm[0] == NULL)
		return ((void)free(comm));
	add_history(str);
	input = ft_inputstruct(comm, vars);
	ft_freestrarr(&comm, 0);
	if (!input)
		return ;
	vars->input = input;
	ft_execute2(input, vars);
	if (input)
		ft_freeinput(&input, vars->np, vars);
	ft_newexit(vars);
}

static void	ft_main1(char *prompt, char *input, t_vars *vars)
{
	ft_signal(PROMPT);
	g_signal = 0;
	prompt = getcwd(NULL, 0);
	if (!prompt)
	{
		ft_putstr_fd("minishell: working directory not found\n", 2);
		ft_putstr_fd("exiting minishell\n", 2);
		ft_exit(NULL, NULL, 1, vars);
	}
	vars->prompt = ft_strjoin(prompt, "-> ");
	free(prompt);
	if (!vars->prompt)
	{
		perror("malloc");
		ft_exit(NULL, NULL, 1, vars);
	}
	input = readline(vars->prompt);
	if (!input)
		ft_exitbuiltin(input, NULL, vars->exit_status, vars);
	do_stuff(input, vars);
	free(vars->prompt);
	vars->prompt = NULL;
}

int	main(int narg, char **argv, char **envp)
{
	char	*input;
	char	*prompt;
	t_vars	vars;

	g_signal = PROMPT;
	ft_signal(PROMPT);
	ft_printf("Welcome to minishell\n");
	ft_init(&vars, envp);
	prompt = NULL;
	input = NULL;
	while (narg == 1 && argv[0])
		ft_main1(prompt, input, &vars);
	return (0);
}
