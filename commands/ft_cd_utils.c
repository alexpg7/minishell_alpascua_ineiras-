
#include "../src/minishell.h"

int	ft_setenv_var(t_vars *vars, char *pwd, char *var_name)
{
	t_list	*env;
	int		var_size;

	var_size = ft_strlen(var_name);
	env = vars->env;
	while (env && ft_strncmp(env->content, var_name, var_size) != 0)
		env = env->next;
	if (env)
	{
		free(env->content);
		env->content = ft_strjoin(var_name, pwd); // Preguntar Alex por si modifican PWD a PWDDD;
		if (!env->content)
			ft_exit(NULL, 1, vars);
		return (0);
	}
	return (1);
}

char	*ft_getenv_var(t_vars *vars, char *var_name)
{
	t_list	*env;
	int		var_size;

	var_size = ft_strlen(var_name);
	env = vars->env;
	while (env && ft_strncmp(env->content, var_name, var_size) != 0)
		env = env->next;
	if (!env)
		return NULL;
	return (env->content);
}
