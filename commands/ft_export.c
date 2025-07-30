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

	env = vars->env;
	while (env)
	{
		if (ft_strncmp(str, env->content, ft_varlen(str) + 1) == 0)
		{
			free(env->content);
			env->content = new_var(vars, str); //protec
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
		if (ft_strisalnum2(*arg) == 0 && **arg != '?')
		{
			arg++;
			continue ;
		}
		if (ft_inenv(*arg, vars))
			ft_subsenv(*arg, vars);
		else
		{
			ft_lstadd_back(&vars->env, ft_lstnew(new_var(vars, *arg)));//protect
		}
		arg++;
	}
}

char	*new_var(t_vars *vars, char *arg)
{
	char	*str;
	char	*str_ae;
	char	*str_en;

	if (!arg)
		return (NULL);
	str = ft_strdup_eq(arg);
	if (!str)
		ft_exit(NULL, 1, vars);
	str_ae = ft_strdup(ft_strchr(arg, '=') + 1);
	if (!str_ae)
		ft_exit(NULL, 1, vars);
	str_ae =  ft_removequotes(ft_searchdollar(str_ae, vars));
	if (!str_ae)
		ft_exit(NULL, 1, vars);
	str_en = ft_strjoin(str, str_ae);
	ft_free_both(str, str_ae);
	return (str_en);
}