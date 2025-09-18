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

void	ft_newexit(t_vars *vars, int n)
{
	char	*num;
	char	*com;

	if (n == 130)
		vars->exit_status = 130;
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
	vars->exit_status = 0;
	g_signal = 0;
}

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
	ft_newexit(vars, 0);
}

static void	ft_main1(char *prompt, char *input, t_vars *vars)
{
	ft_signal(PROMPT);
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
		ft_exitbuiltin(NULL, NULL, vars->exit_status, vars);
	if (g_signal == SIGINT)
		ft_newexit(vars, 130);
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
	ft_putstr_fd("Welcome to minishell\n", 2);
	ft_init(&vars, envp);
	prompt = NULL;
	input = NULL;
	if (narg > 1)
		return (ft_1command(narg - 1, argv + 1, &vars));
	while (narg == 1 && argv[0])
		ft_main1(prompt, input, &vars);
	return (0);
}
