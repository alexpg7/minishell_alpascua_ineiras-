#include "../src/minishell.h"

void	ft_freeall(t_vars *vars)
{
	if (vars->prompt)
		free(vars->prompt);
}

void	ft_exit(char *input, int ret, t_vars *vars)
{
	if (input)
		free(input);
	rl_clear_history();
	//Should clear all malloc-ed storage
	ft_freeall(vars);
	if (vars->np >= 1)
	{
		free(vars->pid);
		ft_freepip(vars->pip, vars->np, vars->np + 1);
	}
	ft_lstclear_lst(&vars->ts);
	if (vars->command)
		ft_freecommand(vars->command);
	ft_lstclear(&vars->env, &free);
	exit(ret);
}
