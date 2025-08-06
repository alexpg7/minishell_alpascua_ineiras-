/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:26:21 by ineiras-          #+#    #+#             */
/*   Updated: 2025/08/05 19:03:00 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	change_old_pwd(t_vars *vars, char *old_pwd)
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

void	change_pwd(t_vars *vars, char *pwd)
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

void	swap_pwd(t_vars *vars)
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
	chdir(content_2 + 7);
	ft_free_both(content, content_2);
}

void	ft_free_both(char *str1, char *str2)
{
	free(str1);
	free(str2);
}

void	ft_free_three(char *str1, char *str2, char *str3)
{
	free(str1);
	free(str2);
	free(str3);
}
