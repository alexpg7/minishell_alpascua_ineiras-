
#include "../src/minishell.h"

static void change_old_pwd(t_vars *vars, char *old_pwd)
{
	t_list	*env;

	env = vars->env;
	while (env && ft_strncmp("OLDPWD=", env->content, 7) != 0)
		env = env->next;
	if (ft_strncmp("HOME=", old_pwd, 5) == 0)
		env->content = ft_strjoin("OLDPWD=", old_pwd + 5);
	if (ft_strncmp("PWD=", old_pwd, 4) == 0)
		env->content = ft_strjoin("OLDPWD=", old_pwd + 4);
}

static void	slash_cd(t_vars *vars)
{
	t_list	*env;

	env = vars->env;
	while (env && ft_strncmp(env->content, "PWD=", 4) != 0)
		env = env->next;
	change_old_pwd(vars, env->content);
	env->content = ft_strjoin("PWD=", "/");
}

static void	cd_not_args(t_vars *vars)
{
	t_list	*env;
	char	*content;

	env = vars->env;
	while (env && ft_strncmp(env->content, "HOME=", 5) != 0)
		env = env->next; 
	content = ft_strjoin("PWD=", env->content + 5);
	env = vars->env;
	while (env && ft_strncmp(env->content, "PWD=", 4) != 0)
		env = env->next;
	//ft_printf("%s", env->content);
	change_old_pwd(vars, env->content);
	env->content = content;
}
 
void ft_cd(t_vars *vars, char **argv)
{
	int argc;
	
	argc = count_args(argv);

	if (argc == 1)
		cd_not_args(vars);
	else if ((argc == 2) && (ft_strcmp(argv[1], "/") == 0))
	{
		slash_cd(vars);
	}
	/*
	if ((argc == 2) && (ft_strcmp(argv[1], "/") == 0))
	cd_not_args(vars, argv);
	if ((argc == 2) && (ft_strcmp(argv[1], "~") == 0))
	cd_not_args(vars, argv);
	if ((argc == 2) && (ft_strcmp(argv[1], ".") == 0))git
	cd_not_args(vars, argv);
	if ((argc == 2) && (ft_strcmp(argv[1], "..") == 0))
	cd_not_args(vars, argv);
	{
	cd_not_args(vars, argv);
	*/

}