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
	ft_lstclear_lst(&vars->ts);
	ft_lstclear(&vars->env, &free);
	ft_lstclear(&vars->export, &free); //should delete export from vars at some point
	//ft_printf("Exiting minishell\n");
	exit(ret);
}
