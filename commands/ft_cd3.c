/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:30:08 by ineiras-          #+#    #+#             */
/*   Updated: 2025/08/04 18:33:55 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	cd_double_point(t_vars *vars)
{
	t_list	*env;
	char	*content;

	env = vars->env;
	while (env && ft_strncmp(env->content, "PWD=", 4) != 0)
		env = env->next;
	content = minus_dir(env->content, vars);
	if (!content)
		ft_exit(NULL, 1, vars);
	change_old_pwd(vars, env->content);
	free(env->content);
	env->content = content;
	chdir(env->content + 4);
}
