/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:52:27 by alpascua          #+#    #+#             */
/*   Updated: 2025/03/13 11:57:22 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	char	*aux;
	char	*ptr;

	aux = ft_strjoin(s1, s2);
	if (!aux)
		return (NULL);
	ptr = ft_strjoin(aux, s3);
	free(aux);
	if (!ptr)
		return (NULL);
	return (ptr);
}
