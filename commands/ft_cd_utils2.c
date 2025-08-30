
#include "../src/minishell.h"

void	ft_create_var(t_vars *vars, char *pwd, char *var_name)
{
	char	*tmp;

	tmp = ft_strjoin(var_name, pwd);
	if (!tmp)
	{
		free(pwd);
		ft_exit(NULL, 1, vars);
	}
	ft_export(vars, &tmp, 1);
	free(tmp);
}

void	ft_path_fail(t_vars *vars, char *pwd, char *error_m)
{
	if (pwd)
		free(pwd);
	vars->exit_status = 1;
	ft_putendl_fd(error_m, 2);
}

void	ft_free_both(char *str1, char *str2)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
}

void	ft_free_three(char *str1, char *str2, char *str3)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (str3)
		free(str3);
}

