/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:23:22 by ineiras-          #+#    #+#             */
/*   Updated: 2025/08/30 17:09:26 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	ft_env(t_vars *vars)
{
	t_list	*lst;

	lst = vars->env->next;
	while (lst)
	{
		if (ft_strchr(lst->content, '='))
		{
			if (ft_strncmp((char *)lst->content, "?=", 2) != 0)
				ft_printf("%s\n", (char *)lst->content);
		}
		lst = lst->next;
	}
	vars->exit_status = 0;
}

char	**ft_getenv(t_list *env)
{
	int		size;
	int		i;
	char	**ptr;
	t_list	*env2;

	env2 = env->next;
	size = ft_lstsize(env2);
	ptr = (char **)malloc(sizeof(char *) * (size));
	if (!ptr)
		return (NULL);
	i = 0;
	while (env2 && i < size)
	{
		if (ft_strncmp((char *)(env2->content), "?=", 2) == 0)
		{
			i++;
			env2 = env2->next;
			continue ;
		}
		ptr[i] = ft_strjoin(env2->content, "");
		if (!ptr[i])
		{
			ft_free(ptr, i);
			return (NULL);
		}
		i++;
		env2 = env2->next;
	}
	ptr[i] = NULL;
	return (ptr);
}
