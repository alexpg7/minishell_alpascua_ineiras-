#include "minishell.h"

void	ft_init(t_vars *vars, char **envp)
{
	t_list	*env;
	t_list	*new;
	int		i;

	i = 1;
	env = ft_lstnew(ft_strjoin(envp[0], ""));//protect
	if (!env)
		ft_exit(NULL, 1, vars);
	while (envp[i])
	{
		new = ft_lstnew(ft_strjoin(envp[i], "")); // protect
		if (!new)
			ft_lstclear(&env, &free);
		ft_lstadd_back(&env, new);
		i++;
	}
	vars->env = env;
	vars->np = 0;
	vars->command = NULL;
	vars->ts = ft_lstnew_lst(NULL, NULL);//protect
}
