/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:23:22 by ineiras-          #+#    #+#             */
/*   Updated: 2025/08/04 18:23:23 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	ft_env(t_vars *vars)
{
	t_list	*lst;

	lst = vars->env->next; //the first one is empty/auxiliar NOT TESTED YET
	while (lst)
	{
		if (ft_strncmp((char *)lst->content, "?=", 2) != 0)
			ft_printf("%s\n", (char *)lst->content);
		lst = lst->next;
	}
	vars->exit_status = 0;
}

char	**ft_getenv(t_list *env)
{
	int		size;
	int		i;
	char	**ptr;

	size = ft_lstsize(env);
	ptr = (char **)malloc(sizeof(char *) * (size + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (env && i < size)
	{
		ptr[i] = ft_strjoin(env->content, "");
		if (!ptr[i])
		{
			ft_free(ptr, i);
			return (NULL);
		}
		i++;
		env = env->next;
	}
	ptr[i] = NULL;
	return (ptr);
}
