/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:47:11 by alpascua          #+#    #+#             */
/*   Updated: 2025/01/12 14:32:17 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	cont;

	cont = 0;
	if (!lst)
		return (0);
	while (lst->next != NULL)
	{
		cont++;
		lst = lst->next;
	}
	return (cont + 1);
}
