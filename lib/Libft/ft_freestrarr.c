/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freestrarr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:00:19 by alpascua          #+#    #+#             */
/*   Updated: 2025/03/13 12:04:47 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_freestrarr(char ***array, int ret)
{
	int	i;

	i = 0;
	if (!(*array) || !(**array))
		return (ret);
	while ((*array)[i])
	{
		free((*array)[i]);
		i++;
	}
	free(*array);
	return (ret);
}
