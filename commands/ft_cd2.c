/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:17:02 by ineiras-          #+#    #+#             */
/*   Updated: 2025/08/30 17:22:42 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	ft_cd_double_point(t_vars *vars)
{
	char	*pwd;
	char	*new_pwd;

	pwd = ft_new_pwd();
	if (!pwd)
		ft_exit(NULL, 1, vars);
	if (!ft_getenv_var(vars, "PWD="))
		ft_create_var(vars, pwd, "PWD=");
	new_pwd = minus_dir(pwd, vars);
	if (!new_pwd)
	{
		free(pwd);
		ft_exit(NULL, 1, vars);
	}
	chdir(new_pwd);
	if (ft_setenv_var(vars, pwd, "OLDPWD=") != 0)
		ft_create_var(vars, pwd, "OLDPWD=");
	if (!ft_setenv_var(vars, new_pwd, "PWD="))
		ft_create_var(vars, new_pwd, "PWD=");
	ft_free_both(pwd, new_pwd);
}

void	ft_swap_pwd(t_vars *vars)
{
	char	*pwd;
	char	*old_pwd;

	pwd = NULL;
	old_pwd = ft_getenv_var(vars, "OLDPWD=");
	if (!old_pwd)
	{
		ft_path_fail(vars, pwd, "cd: OLDPWD not set");
		return ;
	}
	pwd = ft_new_pwd();
	if (!pwd)
		ft_exit(NULL, 1, vars);
	if (chdir (old_pwd + 7) == -1)
	{
		ft_path_fail(vars, pwd, "wrong path set");
		return ;
	}
	ft_set_both(vars, pwd);
}
