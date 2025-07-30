#include "minishell.h"

void	ft_init2(t_vars *vars)
{
	t_list	*new;

	new = ft_lstnew(ft_strjoin("?=0", "")); // protect
	if (!new)
		ft_lstclear(&vars->env, &free);
	ft_lstadd_back(&vars->env, new);
}

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
	vars->envp = NULL;
	vars->env = env;
	vars->exit_status = 0;
	vars->np = 0;
	vars->command = NULL;
	vars->ts = ft_lstnew_lst(NULL, NULL);//protect
	ft_init2(vars);
}
