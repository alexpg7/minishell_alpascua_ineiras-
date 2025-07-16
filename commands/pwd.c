#include "../src/minishell.h"

char	*ft_pwd(char **comm, t_vars *vars)
{
	t_list	*env;

	if (*comm != NULL)
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return (NULL);
	}
	env = vars->env;
	while (env && ft_strncmp(env->content, "PWD=", 4) != 0)
	{
		env = env->next;
	}
	return (env->content + 4);
}
