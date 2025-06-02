#include "../src/minishell.h"

static void	ft_addenv(t_vars *vars, char *arg)
{
	t_list	*new;

	new = ft_lstnew(arg); //trashlist
	if (!new)
		ft_exit(NULL, 1, vars);
	ft_lstadd_back(&vars->env, new);
}

void	ft_export(t_vars *vars, char *arg)
{
	char	*loc;
	int		flagnew;

	flagnew = 0;
	loc = ft_strchr(arg, '=');
	if (!loc)
		flagnew = 1;
	//should also change the 'export' display
	if (flagnew == 0)
	{
		ft_addenv(vars, arg);
	}
}
