/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 12:15:47 by alpascua          #+#    #+#             */
/*   Updated: 2025/01/12 14:40:16 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*aux;

	aux = *lst;
	if (lst && *lst)
	{
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = new;
		while (new->next != NULL)
			new = new->next;
		new->next = NULL;
	}
	else if (lst)
		*lst = new;
	new->next = NULL;
}
