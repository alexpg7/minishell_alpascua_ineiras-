#include "../src/minishell.h"

static int	ft_varlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

static void	ft_subsenv(char *str, t_vars *vars)
{
	t_list	*env;
	char	*aux;

	env = vars->env;
	while (env)
	{
		if (ft_strncmp(str, env->content, ft_varlen(str) + 1) == 0)
		{
			aux = env->content;
			env->content = ft_strjoin(ft_searchdollar(str, vars), ""); //protect
			free(aux);
		}
		env = env->next;
	}
}

int	ft_inenv(char *str, t_vars *vars)
{
	t_list	*env;

	env = vars->env;
	while (env)
	{
		if (ft_strncmp(str, env->content, ft_varlen(str) + 1) == 0)
		{
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void	ft_export(t_vars *vars, char **arg)
{
	if (!(*arg))
	{
		ft_env(vars);
		return ;
	}
	while (arg && ft_strchr(*arg, '='))//execute export for each argument
	{
		if (ft_strisalnum2(*arg) == 0)
		{
			arg++;
			continue ;
		}
		if (ft_inenv(*arg, vars))
		{
			ft_subsenv(*arg, vars);
		}
		else
		{
			ft_lstadd_back(&vars->env, ft_lstnew(ft_strjoin(ft_searchdollar(*arg, vars), "")));//protect
		}
		arg++;
	}
}
