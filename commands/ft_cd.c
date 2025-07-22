#include "../src/minishell.h"

static char	*ft_set_path(t_vars *vars, char *path, char **argv)
{
	if (ft_strncmp(argv[1], "/", 1) == 0 && ft_strlen(argv[1]) == 1)
		path = ft_strjoin("", argv[1]);
	else if (ft_strncmp(argv[1], "/", 1) == 0 && ft_strlen(argv[1]) > 1)
		path = ft_strjoin("", argv[1]);
	else
		path = ft_strjoin3(ft_pwd(&path, vars), "/", argv[1]);
	return (path);
}

static void cd_double_point(t_vars *vars)
{
	t_list *env;
	char	*content;

	env = vars->env;
	while (env && ft_strncmp(env->content, "PWD=", 4) != 0)
		env = env->next;
	content = minus_dir(env->content, vars);
	if (!content)
		ft_exit(NULL, 1, vars);
	change_old_pwd(vars, env->content);
	env->content = content;
	chdir(env->content + 4);
}

static int	cd_move_dir(t_vars *vars, char **argv, char *content, char *path) // No leaks
{
	DIR		*directory;
	t_list	*env;

	path = ft_set_path(vars, path, argv);
	if (!path)
		ft_exit(NULL, 1, vars);
	directory = opendir(path);
	if (!directory)
		return (ft_free_minus_one(path));
	env = vars->env;
	while (env && ft_strncmp(env->content, "PWD=", 4) != 0)
		env = env->next;
	change_old_pwd(vars, env->content);
	free(env->content);
	chdir(path);
	content = ft_strjoin("PWD=", ft_new_pwd());
	env->content = content;
	if (!env->content)
		ft_exit(NULL, 1, vars);
	closedir(directory);
	free(path);
	return (0);
}

static void cd_argc_2(t_vars *vars, char **argv)
{
	char *content;
	char *path;

	content = NULL;
	path = NULL;
	if (ft_strcmp(argv[1], "/") == 0)
		cd_move_dir(vars, argv, content, path);
	else if (ft_strcmp(argv[1], "-") == 0)
		swap_pwd(vars);		
	else if (ft_strcmp(argv[1], ".") == 0)
		;
	else if(ft_strcmp(argv[1], "..") == 0)
		cd_double_point(vars);
	else if (cd_move_dir(vars, argv, content, path) == -1)
		ft_putendl_fd2("cd: not such file or directory: ", 2, argv[1]);
}

static void	cd_not_args(t_vars *vars)
{
	t_list	*env;
	char	*content;

	env = vars->env;
	while (env && ft_strncmp(env->content, "HOME=", 5) != 0)
		env = env->next;
	content = ft_strjoin("PWD=", env->content + 5);
	if (!content)
		ft_exit(NULL, 1, vars);
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
		cd_argc_2(vars, argv);
	else if (argc == 3)
		ft_putendl_fd2("cd: string not in pwd: ", 2, argv[1]);
	else
		ft_putendl_fd("cd: too many arguments", 2);
}