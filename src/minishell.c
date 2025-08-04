/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 20:05:01 by alpascua          #+#    #+#             */
/*   Updated: 2025/07/30 20:05:04 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	g_shell_state;

void	ft_newexit(t_vars *vars)
{
	char	*num;
	char	*com;

	num = ft_itoa(vars->exit_status);
	if (!num)
		ft_exit(NULL, 1, vars);
	com = ft_strjoin("?=", num);
	free(num);
	if (!com)
		ft_exit(NULL, 1, vars);
	ft_export(vars, &com, 1);
	free(com);
}

void	ft_printcom(t_command *comm)
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

void	ft_freecommand(t_command *command)
{
	int	i;

	i = 0;
	while (command[i].comm)
	{
		free(command[i].comm);
		i++;
	}
	free(command);
}

void	do_stuff(char *str, t_vars *vars)
{
	char	**comm;
	t_lst	*ts;

	vars->np = 0;
	vars->command = NULL;
	comm = ft_splitmini(str, ' ', vars);
	free(str);
	if (!comm)
		ft_exit(NULL, 1, vars);
	if (comm[0] == NULL)
		return ;
	if (vars->command)
		ft_freecommand(vars->command);
	vars->command = ft_createcomm(comm, vars);
	ts = ft_lstnew_lst(NULL, (void **)comm);
	if (!ts)
		ft_exit(NULL, ft_freestrarr(&comm, 2), vars);
	ft_lstadd_back_lst(&vars->ts, ts);
	ft_execute(vars->command, vars);
	ft_freecommand(vars->command);
	vars->command = NULL;
	ft_newexit(vars);
}

int	main(int narg, char **argv, char **envp)
{
	char	*input;
	char	*nul;
	t_vars	vars;

	g_shell_state = PROMPT;
	ft_init_sig();
	nul = NULL;
	ft_printf("Welcome to minishell\n");
	ft_init(&vars, envp);
	while (narg == 1 && argv[0])
	{
		vars.prompt = ft_strjoin(ft_pwd(&nul, &vars), "-> ");
		if (!vars.prompt)
		{
			perror("malloc");
			ft_exit(NULL, 1, &vars);
		}
		input = readline(vars.prompt);
		if (!input)
			ft_exit(input, 1, &vars);
		add_history(input);
		do_stuff(input, &vars);
		free(vars.prompt);
	}
	return (0);
}
