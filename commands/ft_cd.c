
#include "../src/minishell.h"

static char	*ft_set_path(t_vars *vars, char *path, char **argv)
{
	char	*pwd;

	pwd =  ft_new_pwd();
	if (!pwd)
		ft_exit(NULL, 1, vars);
	if (ft_strncmp(argv[1], "/", 1) == 0 && ft_strlen(argv[1]) == 1)
		path = ft_strjoin("", argv[1]);
	else if (ft_strncmp(argv[1], "/", 1) == 0 && ft_strlen(argv[1]) > 1)
		path = ft_strjoin("", argv[1]);
	else
		path = ft_strjoin3(pwd, "/", argv[1]);
	free(pwd);
	return (path);
}

int	ft_cd_move_dir(t_vars *vars, char **argv, char *path)
{
	DIR		*directory;
	char	*pwd;

	path = ft_set_path(vars, path, argv);
	if (!path)
		ft_exit(NULL, 1, vars);
	directory = opendir(path);
	if (!directory)
		return (ft_free_minus_one(path));
	pwd = ft_new_pwd();
	if (!pwd)
		ft_exit(NULL, 1, vars);
	if (ft_setenv_var(vars, pwd, "OLDPWD=") != 0)
		ft_create_var(vars, pwd, "OLDPWD=");
	chdir(path);
	ft_free_both(path, pwd);
	pwd = ft_new_pwd();
	if (!pwd)
		ft_exit(NULL, 1, vars);
	if (ft_setenv_var(vars, pwd, "PWD=") != 0)
		ft_create_var(vars, pwd, "PWD=");
	closedir(directory);
	free(pwd);
	return (0);
}

void	ft_cd_two_arg(t_vars *vars, char **argv)
{
	char	*path;

	path = NULL;
	if (ft_strcmp(argv[1], "/") == 0)
		ft_cd_move_dir(vars, argv, path);
	else if (ft_strcmp(argv[1], "-") == 0)
		ft_swap_pwd(vars);
	else if (ft_strcmp(argv[1], ".") == 0)
		;
	else if (ft_strcmp(argv[1], "..") == 0)
		ft_cd_double_point(vars);
	else if (ft_cd_move_dir(vars, argv, path) == -1)
		ft_putendl_fd2("cd: not such file or directory: ", 2, argv[1]);
}

void  ft_cd_not_args(t_vars *vars)
{
	char	*home;
	char	*pwd;

	home = ft_getenv_var(vars, "HOME=");
	if (!home)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		vars->exit_status = 1;
		return;
	}
	pwd = ft_new_pwd();
	if (!pwd)
		ft_exit(NULL, 1, vars);
	if (chdir(home + 5) == - 1)
	{
		ft_path_fail(vars, pwd, "wrong path set" );
		return;
	}
	if (ft_setenv_var(vars, pwd, "OLDPWD=") != 0)
		ft_create_var(vars, pwd, "OLDPWD=");
	free(pwd);
	pwd = ft_new_pwd();
	if (!pwd)
		ft_exit(NULL, 1, vars);
	if (ft_setenv_var(vars, pwd, "PWD=") != 0)
		ft_create_var(vars, pwd, "PWD=");
	free(pwd);
}

void	ft_cd(t_vars *vars, char **argv)
{
	int	argc;

	argc = count_args(argv);
	if (argc == 1 || (argc == 2 && ft_strcmp(argv[1], "~") == 0))
		ft_cd_not_args(vars);
	else if (argc == 2)
		ft_cd_two_arg(vars, argv);
	else if (argc == 3)
	{
		ft_putendl_fd2("cd: string not in pwd: ", 2, argv[1]);
		vars->exit_status = 1;
	}
	else
	{
		ft_putendl_fd("cd: too many arguments", 2);
		vars->exit_status = 1;
	}
}
