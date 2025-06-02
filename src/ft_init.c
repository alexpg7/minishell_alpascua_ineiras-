#include "minishell.h"

void	ft_init(t_vars *vars, char **envp)
{
	t_list	*env;
	t_list	*new;
	int		i;

	i = 1;
	env = ft_lstnew(envp[0]);
	if (!env)
		ft_exit(NULL, 1, vars);
	while (envp[i])
	{
		new = ft_lstnew(envp[i]);
		if (!new)
			ft_lstclear(&env, &free);
		ft_lstadd_back(&env, new);
		i++;
	}
	vars->env = env;
}
