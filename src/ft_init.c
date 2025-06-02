#include "minishell.h"

void	ft_init(t_vars *vars, char **envp)
{
	t_list	*env;
	t_list	*exp;
	t_list	*new;
	int		i;

	i = 1;
	env = ft_lstnew(envp[0]);
	exp = ft_lstnew(envp[0]);
	if (!env || !exp)
		ft_exit(NULL, 1, vars);
	while (envp[i])
	{
		new = ft_lstnew(envp[i]);
		if (!new)
			ft_lstclear(&env, &free);
		ft_lstadd_back(&env, new);//add to trash
		new = ft_lstnew(envp[i]);
		if (!new)
			ft_lstclear(&exp, &free);
		ft_lstadd_back(&exp, new);//add to trash
		i++;
	}
	vars->env = env;
	vars->export = exp;
}
