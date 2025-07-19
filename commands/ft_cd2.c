#include "../src/minishell.h"

void change_old_pwd(t_vars *vars, char *old_pwd) // Changes $OLD_PWD for current PWW;
{
	t_list	*env;

	env = vars->env;
	while (env && ft_strncmp("OLDPWD=", env->content, 7) != 0)
		env = env->next;
	if (ft_strncmp("HOME=", old_pwd, 5) == 0)
	{
		free(env->content);
		env->content = ft_strjoin("OLDPWD=", old_pwd + 5);
	}
	else if (ft_strncmp("PWD=", old_pwd, 4) == 0)
	{
		free(env->content);
		env->content = ft_strjoin("OLDPWD=", old_pwd + 4);
	}
	if (!env->content)
		ft_exit(NULL, 1, vars);
}

void change_pwd(t_vars *vars, char *pwd) // Changes $PWD for $OLD_PWD;
{
	t_list	*env;

	env = vars->env;
	while (env && ft_strncmp("PWD=", env->content, 4) != 0)
		env = env->next;
	if (ft_strncmp("OLDPWD=", pwd, 7) == 0)
	{
		free(env->content);
		env->content = ft_strjoin("PWD=", pwd + 7);
	}
	if (!env->content)
		ft_exit(NULL, 1, vars);
}

void swap_pwd(t_vars *vars)
{
	t_list	*act_env;
	t_list	*old_env;
	char	*content;
	char	*content_2;

	act_env = vars->env;
	old_env = vars->env;
	while (act_env && ft_strncmp("PWD=", act_env->content, 4) != 0)
		act_env = act_env->next;
	content = ft_strjoin("", act_env->content);
	if (!content)
		ft_exit(NULL, 1, vars);
	while (old_env && ft_strncmp("OLDPWD=", old_env->content, 7) != 0)
		old_env = old_env->next;
	content_2 = ft_strjoin("", old_env->content);
	if (!content_2)
		ft_exit(NULL, 1, vars);
	change_old_pwd(vars, content);
	change_pwd(vars, content_2);
	chdir(content_2 + 4);
	free(content);
	free(content_2);
}