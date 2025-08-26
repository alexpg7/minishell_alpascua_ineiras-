/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:22:34 by ineiras-          #+#    #+#             */
/*   Updated: 2025/08/04 18:23:01 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

char	*ft_pwd(char **comm, t_vars *vars)
{
	t_list	*env;

	if (*comm != NULL)
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);// exit status to 1
		vars->exit_status = 1;
		return (NULL);
	}
	env = vars->env;//getcwd, not search PWD
	while (env && ft_strncmp(env->content, "PWD=", 4) != 0)
	{
		env = env->next;
	}
	return (env->content + 4);
}

char	*ft_new_pwd(void)
{
	char	*cwd;

	cwd = NULL;
	return (getcwd(cwd, 0));
}
