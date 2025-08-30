/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_execmore_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:49:05 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/30 17:49:07 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

int	**ft_freepip(int **arr, int len, int index)
{
	int	i;
	int	**aux;

	i = 0;
	aux = arr;
	while (i < len && i < index - 1)
	{
		free(arr[i]);
		i++;
	}
	free(aux);
	return (NULL);
}

int	**ft_pipalloc(int len)
{
	int	i;
	int	**ptr;

	i = 0;
	ptr = (int **)malloc(sizeof(int *) * len);
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		ptr[i] = (int *)malloc(sizeof(int) * 2);
		if (!ptr[i])
			return (ft_freepip(ptr, len, i + 1));
		i++;
	}
	return (ptr);
}
