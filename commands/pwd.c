#include "../src/minishell.h"

char	*ft_pwd(t_vars *vars)
{
	t_list	*env;

	env = vars->env;
	while (env && ft_strncmp(env->content, "PWD=", 4) != 0) //SHOULD ALSO MODIFY THE OLDPPWD VARIABLE //CHANGED IN CD FUNCT
	{
		env = env->next;
	}
	return (env->content + 4);
}
