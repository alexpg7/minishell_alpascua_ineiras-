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

int	ft_loop(t_list	**env, int *i, char **ptr)
{
	if (ft_strncmp((char *)((*env)->content), "?=", 2) == 0)
	{
		(*env) = (*env)->next;
		return (1);
	}
	ptr[*i] = ft_strjoin((*env)->content, "");
	if (!ptr[*i])
	{
		ft_free(ptr, *i);
		return (0);
	}
	*i = *i + 1;
	*env = (*env)->next;
	return (1);
}

char	**ft_getenv(t_list *env)
{
	int		size;
	int		i;
	char	**ptr;
	t_list	*env2;

	env2 = env->next;
	size = ft_lstsize(env2) - 1;
	ptr = (char **)malloc(sizeof(char *) * (size + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (env2 && i < size)
	{
		if (ft_loop(&env2, &i, ptr) == 0)
			return (NULL);
	}
	ptr[i] = NULL;
	return (ptr);
}
