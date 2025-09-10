/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:10:32 by ineiras-          #+#    #+#             */
/*   Updated: 2025/08/30 17:23:03 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	ft_create_var(t_vars *vars, char *pwd, char *var_name)
{
	char	*tmp;

	tmp = ft_strjoin(var_name, pwd);
	if (!tmp)
	{
		free(pwd);
		ft_exit(NULL, NULL, 1, vars);
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

void	ft_set_both(t_vars *vars, char *pwd)
{
	if (!pwd)
		ft_exit(NULL, NULL, 1, vars);
	if (ft_setenv_var(vars, pwd, "OLDPWD=") != 0)
		ft_create_var(vars, pwd, "OLDPWD=");
	free(pwd);
	pwd = ft_new_pwd();
	if (!pwd)
		ft_exit(NULL, NULL, 1, vars);
	if (ft_setenv_var(vars, pwd, "PWD=") != 0)
		ft_create_var(vars, pwd, "PWD=");
	free(pwd);
}

void	ft_cd_point(t_vars *vars)
{
	char	*pwd;

	pwd = ft_new_pwd();
	if (!pwd)
		ft_exit(NULL, NULL, 1, vars);
	if (ft_setenv_var(vars, pwd, "PWD=") != 0)
		ft_create_var(vars, pwd, "PWD=");
	if (ft_setenv_var(vars, pwd, "OLDPWD=") != 0)
		ft_create_var(vars, pwd, "OLDPWD=");
	free(pwd);
}
