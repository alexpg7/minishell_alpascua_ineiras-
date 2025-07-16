
#include "../src/minishell.h"

static int	cd_move_dir(t_vars *vars, char **argv)
{
	DIR		*directory;
	t_list	*env;
	char	*path;

	path = NULL;
	path = ft_strjoin3(ft_pwd(&path, vars), "/", argv[1]);
	if (!path)
		return (-1);
	directory = opendir(path);
	if (directory == NULL)
	{
		free(path);
		return (-1);
	}
	env = vars->env;
	while (env && ft_strncmp(env->content, "PWD=", 4) != 0)
		env = env->next;
	change_old_pwd(vars, env->content);
	env->content = ft_strjoin("PWD=", path);
	chdir(path);
	closedir(directory);
	return (0);
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
	chdir(env->content + 4);
}

static void	slash_cd(t_vars *vars)
{
	t_list	*env;

	env = vars->env;
	while (env && ft_strncmp(env->content, "PWD=", 4) != 0)
		env = env->next;
	change_old_pwd(vars, env->content);
	env->content = ft_strjoin("PWD=", "/");
	chdir(env->content + 4);
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
	chdir(env->content + 4);
}

void ft_cd(t_vars *vars, char **argv)
{
	int argc;

	argc = count_args(argv);
	if (argc == 1 || (argc == 2 && ft_strcmp(argv[1], "~") == 0))
		cd_not_args(vars);
	else if (argc == 2)
	{
		if (ft_strcmp(argv[1], "/") == 0)
			slash_cd(vars);
		else if (ft_strcmp(argv[1], "-") == 0)
			swap_pwd(vars);
		else if (ft_strcmp(argv[1], ".") == 0)
			;
		else if(ft_strcmp(argv[1], "..") == 0)
			cd_double_point(vars);
		else if (cd_move_dir(vars, argv) == -1)
			ft_printf("cd: not such file or directory: %s\n", argv[1]);
	}
}
