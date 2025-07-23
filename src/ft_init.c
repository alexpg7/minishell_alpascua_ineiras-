#include "minishell.h"

void	ft_init(t_vars *vars, char **envp)
{
	t_list	*env;
	t_list	*exp;
	t_list	*new;
	int		i;

	i = 1;
	env = ft_lstnew(ft_strjoin(envp[0], ""));//protect
	exp = ft_lstnew(ft_strjoin(envp[0], ""));//protect
	if (!env || !exp)
		ft_exit(NULL, 1, vars);
	while (envp[i])
	{
		new = ft_lstnew(ft_strjoin(envp[i], "")); // protect
		if (!new)
			ft_lstclear(&env, &free);
		ft_lstadd_back(&env, new);
		new = ft_lstnew(ft_strjoin(envp[i], ""));
		if (!new)
			ft_lstclear(&exp, &free);
		ft_lstadd_back(&exp, new);
		i++;
	}
	vars->env = env;
	vars->export = exp;
	vars->np = 0;
	vars->command = NULL;
	vars->ts = ft_lstnew_lst(NULL, NULL);//protect
}
