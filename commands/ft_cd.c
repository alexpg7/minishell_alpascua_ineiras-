
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

static void change_pwd(t_vars *vars, char *new_pwd)
{
	t_list	*env;

	env = vars->env;
	while (env && ft_strncmp("PWD=", env->content, 4) != 0)
		env = env->next;
	/*
	if (ft_strncmp("HOME=", old_pwd, 5) == 0)
		env->content = ft_strjoin("OLDPWD=", old_pwd + 5);*/
	if (ft_strncmp("OLDPWD=", new_pwd, 7) == 0)
		env->content = ft_strjoin("PWD=", new_pwd + 7);
}
/*
static void cd_move(t_vars *vars, char *dir_name)
{

}*/

static void swap_pwd(t_vars *vars)
{
	t_list	*act_env;
	t_list	*old_env;
	char	*content;
	char	*content_2;

	act_env = vars->env;
	old_env = vars->env;

	while (act_env && ft_strncmp("PWD=", act_env->content, 4) != 0)
		act_env = act_env->next;
	content = act_env->content;
	while (old_env && ft_strncmp("OLDPWD=", old_env->content, 7) != 0)
		old_env = old_env->next;
	content_2 = old_env->content;
	change_old_pwd(vars, content);
	change_pwd(vars, content_2);
}

static void cd_double_point(t_vars *vars)
{
	t_list *env;
	char	*content;

	env = vars->env;
	while (env && ft_strncmp(env->content, "PWD=", 4) != 0)
		env = env->next;
	content = minus_dir(env->content);
	change_old_pwd(vars, env->content);
	env->content = content;
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
	change_old_pwd(vars, env->content);
	env->content = content;
}

void ft_cd(t_vars *vars, char **argv)
{
	int argc;
	DIR *directory;

	argc = count_args(argv);
	if (argc == 1 || (argc == 2 && ft_strcmp(argv[1], "~") == 0))
		cd_not_args(vars);
	else if (argc == 2)
	{
		directory = opendir(ft_strjoin3(ft_pwd(vars), "/", argv[1]));
		if (ft_strcmp(argv[1], "/") == 0)
			slash_cd(vars);
		if (ft_strcmp(argv[1], "-") == 0)
			swap_pwd(vars);
		else if (ft_strcmp(argv[1], ".") == 0)
			;
		else if(ft_strcmp(argv[1], "..") == 0)
			cd_double_point(vars);
		else if (directory != NULL)
		{
			//cd_move_dir("yes\n");
			closedir(directory);
		}
		else
			ft_printf("cd: not such file or directory: %s\n", argv[1]);
	}
}
